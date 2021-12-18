#include "server.hpp"

server::server() {
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	
	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	FD_ZERO(&reads);
	FD_SET(server_fd,&reads);
	fd_max = server_fd;
}

void server::start() {
	while(1) {
		cpy_reads = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

		if ((fd_num = select(fd_max+1, &cpy_reads, 0, 0, &timeout)) == -1)
            break;

        if (fd_num == 0)
            continue;

        for (int i=0; i<fd_max+1; i++) {
            if (FD_ISSET(i, &cpy_reads)) { // fd_set 테이블을 검사한다.
                // 서버 소켓(리스닝 소켓)에 이벤트(연결 요청) 발생
                if (i == server_fd) {     // connection request!
					clnt_sock = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen);
                    FD_SET(clnt_sock, &reads); // fd_set 테이블에 클라이언트 소켓 디스크립터를 추가한다.
                    if (fd_max < clnt_sock)
                        fd_max = clnt_sock;
                    printf("connected client: %d \n", clnt_sock);
					char num[10];
					sprintf(num,"%d",clnt_sock);
					send(clnt_sock,num,10,0);
                }
                // 클라이언트와 연결된 소켓에 이벤트 발생
                else {   // read message!
                    str_len = read(i, buffer, buffer_size);
                    if (str_len == 0) {   // close request!
                        FD_CLR(i, &reads); // fd_set 테이블에서 파일 디스크립터를 삭제한다.
                        close(i);
                        printf("closed client: %d \n", i);
                    } else {
                    }
                }
            }
        }
	}
}

void server::send_string(char * str) {
	send(clnt_sock,str,strlen(str), 0 );
	return;
}