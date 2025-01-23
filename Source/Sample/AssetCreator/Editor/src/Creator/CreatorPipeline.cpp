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

				// 等待信号量，最多等待2秒
				{
					boost::unique_lock<boost::mutex> lock(m_mtx);
					m_waiting = true;

					if (!m_cv.wait_for(lock, boost::chrono::seconds(1), [this]() { return !m_signals.empty(); })) {
						// 超时未触发，检查任务是否结束
						if (m_task_done) {
							std::cout << "Task completed, exiting..." << std::endl;
							break;
						}
						std::cout << "Timeout occurred, no signal received." << std::endl;
					}
					else {
						// 信号到达，处理所有信号
						while (!m_signals.empty()) {
							int signal = m_signals.front();
							m_signals.pop();
							process_signal(signal);
						}
					}

					m_waiting = false; // 重置等待状态
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
			m_cv.notify_all(); // 通知所有线程，可以提前结束
		}

		void request_stop() {
			boost::lock_guard<boost::mutex> lock(m_mtx);
			m_stop_requested = true;
			if (m_waiting) {
				// 如果正在等待信号，唤醒线程以处理停止请求
				m_cv.notify_all();
			}
		}

	private:
		void process_signal(int sig) {
			std::cout << "Processing signal: " << sig << std::endl;
			boost::this_thread::sleep_for(boost::chrono::seconds(1)); // 模拟处理时间
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
		// 创建并启动线程
		boost::thread task_thread(&Task::run, &task);

		boost::this_thread::sleep_for(boost::chrono::seconds(5));
		// 模拟信号发送
		task.signal(1);
		boost::this_thread::sleep_for(boost::chrono::seconds(5));
		//task.signal(2);

		// 模拟请求停止并取消等待
		std::cout << "Requesting stop..." << std::endl;
		task.request_stop();

		// 模拟完成任务
		task.set_done();

		// 等待任务完成并停止线程
		task_thread.join();
	}
}