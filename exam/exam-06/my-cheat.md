1. variable globales
2. copier extract_message() et str_join()
2. fatal()
3. send_all(except, *str)
	- FD_ISSET(fd, &active)...
	- send(fd, str, strlen(str), 0);
4. ac/av == 2
5. socket
	1. < 0 fatal()
	2. update max_fd
6. struct sockaddr_in
7. bind et listen(128)
8. FD_ZERO(&active) et FD_SET(sock_fd, &active)
9. boucle finie
	1. readset = active
	2. select(max_fd+1, &readset, NULL, NULL, NULL)
		- <0 continue
	3. boucle for 0->max_fd
10. pas set continue
11. fd == sock_fd (new co)
	1. accept(sock_fd, NULL, NULL)
	2. <0 continue
	3. maj max_fd ?
	4. ids[c] = next_id++
	5. stock[c] = NULL
	6. FD_SET(c, &active)
	7. sprintf() + send_all()
12. else
	1. r = recv(fd, buf, 1023, 0)
	2. r <= 0
		1. sprintf() + send_all()
		2. free(stock[fd])
		3. FD_CLR(fd, &active)
		4. close(fd)
	3. else
		1. buf[r] = 0
		2. stock[fd] = str_join(stock[fd], buf)
			- !stock[fd] -> fatal()
		3. char	*line
		4. while (extract_message(&stock[fd], &line) == 1)
			1. sprintf() + send_all() du préfixe
			2. send_all(fd, line)
			3. free(line)


BLOCAGES :
select() attend que au moins 1 fd soit prêt parmis ceux présent dans readset entre 0 et max_fd et modifie readset pour mettre que les fd prêts
