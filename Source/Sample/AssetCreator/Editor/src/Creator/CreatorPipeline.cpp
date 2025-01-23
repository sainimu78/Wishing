#include "Creator/CreatorPipeline.h"
#include "boost/thread.hpp"
#include <queue>
#include <iostream>

namespace Wishing
{
	class Task
	{
	public:
		Task()
			: m_task_done(false)
			, m_stop_requested(false)
			, m_waiting(false)
		{
		}
		void run()
		{
			while (true)
			{
				{
					boost::lock_guard<boost::mutex> lock(m_mtx);
					if (m_stop_requested) {
						std::cout << "Task is stopping..." << std::endl;
						break;
					}
				}

				// �ȴ��ź��������ȴ�2��
				{
					boost::unique_lock<boost::mutex> lock(m_mtx);
					m_waiting = true;

					if (!m_cv.wait_for(lock, boost::chrono::seconds(1), [this]() { return !m_signals.empty(); })) {
						// ��ʱδ��������������Ƿ����
						if (m_task_done) {
							std::cout << "Task completed, exiting..." << std::endl;
							break;
						}
						std::cout << "Timeout occurred, no signal received." << std::endl;
					}
					else {
						// �źŵ�����������ź�
						while (!m_signals.empty()) {
							int signal = m_signals.front();
							m_signals.pop();
							process_signal(signal);
						}
					}

					m_waiting = false; // ���õȴ�״̬
				}
			}
		}
		void signal(int sig) {
			{
				boost::lock_guard<boost::mutex> lock(m_mtx);
				m_signals.push(sig);
			}
			m_cv.notify_one();
		}

		void set_done() {
			boost::lock_guard<boost::mutex> lock(m_mtx);
			m_task_done = true;
			m_cv.notify_all(); // ֪ͨ�����̣߳�������ǰ����
		}

		void request_stop() {
			boost::lock_guard<boost::mutex> lock(m_mtx);
			m_stop_requested = true;
			if (m_waiting) {
				// ������ڵȴ��źţ������߳��Դ���ֹͣ����
				m_cv.notify_all();
			}
		}

	private:
		void process_signal(int sig) {
			std::cout << "Processing signal: " << sig << std::endl;
			boost::this_thread::sleep_for(boost::chrono::seconds(1)); // ģ�⴦��ʱ��
		}
		boost::mutex m_mtx;
		boost::condition_variable m_cv;
		std::queue<int> m_signals;
		bool m_task_done;
		bool m_stop_requested;
		bool m_waiting;
	};

	void TestPipeline()
	{
		Task task;
		// �����������߳�
		boost::thread task_thread(&Task::run, &task);

		boost::this_thread::sleep_for(boost::chrono::seconds(5));
		// ģ���źŷ���
		task.signal(1);
		boost::this_thread::sleep_for(boost::chrono::seconds(5));
		//task.signal(2);

		// ģ������ֹͣ��ȡ���ȴ�
		std::cout << "Requesting stop..." << std::endl;
		task.request_stop();

		// ģ���������
		task.set_done();

		// �ȴ�������ɲ�ֹͣ�߳�
		task_thread.join();
	}
}