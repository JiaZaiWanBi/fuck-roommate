import socket
import time
import random

# 配置目标 IP 和端口
target_ip = "223.1.1.1"
target_port = 6666  # 自定义端口，可以更改
mode = 1
percentage = 50
packet_size = 10240  # 每个 UDP 数据包的大小（1024 字节）
packets_per_second = 700  # 每秒发送的包数

# 创建 UDP 套接字
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sleeptime = 1/percentage

print(f"每秒发送 {packets_per_second} 个 {packet_size} 字节的 UDP 数据包，目标地址 {target_ip}:{target_port}")

try:
    while True:
        for _ in range(packets_per_second):
            # 发送一个 1024 字节的 UDP 数据包
            sock.sendto(b"x" * packet_size, (target_ip, target_port))
            
        
        if mode  == 1:
            time.sleep(random.uniform(0.5,3))  # 每秒发送 10 个包
        elif mode == 2:
            time.sleep(percentage)
            
        
        
except KeyboardInterrupt:
    print("\n任务已中断")
finally:
    sock.close()
    print("UDP 套接字已关闭")
    