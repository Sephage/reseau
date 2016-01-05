all : server

server : server.c initGame.c move.c niveau.c
	gcc -o server server.c initGame.c move.c niveau.c -g
	
server2 : server2.c initGame.c move.c niveau.c
	gcc -o server2 server2.c initGame.c move.c niveau.c -g


clean :
	rm -fr server
