VirtualBox 设置的共享文件夹名为 `SharedFolder`

```
sudo mkdir /mnt/SharedFolder_Ubuntu
udo mount -t vboxsf SharedFolder /mnt/SharedFolder_Ubuntu
```











要在 Ubuntu 中挂载 VirtualBox 的共享文件夹（如 `admin:///SharedFolder`），通常你需要执行以下步骤。这里假设你已经在 VirtualBox 中正确设置了共享文件夹。

### 1. 安装 VirtualBox Guest Additions

确保你的虚拟机安装了 VirtualBox Guest Additions。这可以通过以下步骤完成：

- 启动你的 Ubuntu 虚拟机。
- 从 VirtualBox 的菜单中，选择 **Devices** -> **Insert Guest Additions CD Image...**。
- 按照提示安装 Guest Additions，通常你只需在终端中运行安装脚本（如果未自动启动）。

### 2. 创建挂载点

创建你要挂载共享文件夹的挂载点（目录），例如：

```bash
sudo mkdir /mnt/shared
```

### 3. 挂载共享文件夹

使用 `mount` 命令将共享文件夹挂载到你刚才创建的挂载点。假设你在 VirtualBox 中将共享文件夹的名称设置为 `SharedFolder`，可以使用以下命令：

```bash
sudo mount -t vboxsf SharedFolder /mnt/shared
```

### 4. 免密码访问（可选）

如果你希望在访问共享文件夹时不必输入密码，可以将你的用户添加到 `vboxsf` 组。执行下面的命令：

```bash
sudo usermod -aG vboxsf $(whoami)
```

然后登出再重新登录，或者重启虚拟机，使更改生效。

### 5. 自动挂载（可选）

如果你希望在每次启动虚拟机时自动挂载共享文件夹，可以在 `/etc/fstab` 文件中添加一行。执行以下命令打开文件：

```bash
sudo nano /etc/fstab
```

在文件末尾添加如下行：

```
SharedFolder /mnt/shared vboxsf defaults,uid=1000,gid=1000 0 0
```

确保更改 `SharedFolder` 为你的共享文件夹名称， `/mnt/shared` 为你创建的挂载点。

保存并退出，然后你可以通过以下命令测试 `/etc/fstab` 的设置：

```bash
sudo mount -a
```

### 结论

通过按照上述步骤，你可以在 Ubuntu 中挂载 VirtualBox 的共享文件夹，并且可以选择为了避免输入密码而设置用户组权限。每次虚拟机启动时，也可以自动挂载该共享文件夹。