# Network-Programming

- TCP/IP 4계층 이해
- TCP/UDP 프로토콜 이해
- 소켓 구조체 사용 및 이해


## 실습: UDP 기반 소켓  이용해 Server, Clinet 구조로 sin(x) 그리기
- Server: 각도를 받아 라디안으로 전환한 뒤, sin(x) 출력 값을 클라이언트에게 전달
- Client: Server에게 해당 각도에대한 sin(x) 값을 요청한 뒤, 받아와서 terminal 창에 그림

sin(x)는 [-1,1] 이므로,  sin(x) * 20 + 20 연산을 통해, [-40,40] 범위로 매핑한 뒤, 반복문을 통해 '-', 'o' 출력 

![image](https://user-images.githubusercontent.com/48324017/117924172-473e4f00-b330-11eb-8723-223f01fde0c9.png)
