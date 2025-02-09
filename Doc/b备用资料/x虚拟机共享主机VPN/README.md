

![Screenshot 2025-02-09 160841](Screenshot 2025-02-09 160841.png)

勾选后 git 的代理设置可起效, IP 为物理网卡 IP, 如

```
git config --global http.proxy http://192.168.31.233:1080
git config --global https.proxy http://192.168.31.233:1080
```

浏览器访问可通过 Network 的 Network Proxy

![Screenshot 2025-02-09 161242](Screenshot 2025-02-09 161242.png)