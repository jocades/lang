-module(server).
-export([start/0, server/1, connector/1, session/1]).

start() ->
  Port = 8000,
  Opts = [binary, {reuseaddr, true}, {active, once}, {packet, raw}],
  {ok, LSock} = gen_tcp:listen(Port, Opts),
  io:format("Listening on port ~p\n", [Port]),
  register(server, spawn(?MODULE, server, [[]])),
  spawn(?MODULE, connector, [LSock]).

-spec server(Socks) -> no_return() when
    Socks :: list({inet:socket(), pid()}).

server(Socks) ->
  receive
    {sub, Sock, Pid} ->
      NewSocks = [{Sock, Pid} | Socks],
      io:format("[broadcaster] sub: ~p socks: ~p\n", [Sock, NewSocks]),
      server(NewSocks);
    {unsub, Sock} ->
      NewSocks = lists:keydelete(Sock, 1, Socks),
      io:format("[broadcaster] unsub: ~p socks: ~p\n", [Sock, NewSocks]),
      server(NewSocks);
    {pub, FromSock, Message} ->
      [Pid ! {send, Message} || {Sock, Pid} <- Socks, Sock =/= FromSock],
      server(Socks)
  end.

-spec connector(LSock) -> no_return() when
  LSock :: inet:socket().

connector(LSock) ->
  {ok, Sock} = gen_tcp:accept(LSock),
  Pid = spawn(?MODULE, session, [Sock]),
  server ! {sub, Sock, Pid},
  connector(LSock).


-spec session(Sock) -> ok when
    Sock :: inet:socket().

session(Sock) ->
  receive
    % Data from socket
    {tcp, Sock, Packet} ->
      server ! {pub, Sock, Packet},
      inet:setopts(Sock, [{active, once}]),
      session(Sock);

    % Message from other client
    {send, Message} ->
      io:format("[session] send to ~p: ~p\n", [Sock, Message]),
      gen_tcp:send(Sock, Message),
      session(Sock);

    % Connection closed
    {tcp_closed, Sock} ->
      io:format("[session] ~p: disconnected\n", [Sock]),
      server ! {unsub, Sock},
      ok;

    % TCP error
    {tcp_error, Sock, Reason} ->
      io:format("[session] ~p: error ~p\n", [Sock, Reason]),
      server ! {unsub, Sock},
      gen_tcp:close(Sock)

  end.
