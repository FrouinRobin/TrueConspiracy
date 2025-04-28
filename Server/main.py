import asyncio
import time
import subprocess
import socket
import os

def get_local_ip():
    try:
        # This doesn't have to connect to anything — just to get a valid outbound IP
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
            s.connect(("8.8.8.8", 80))
            return s.getsockname()[0]
    except Exception as e:
        print(f"[ERROR] Failed to get local IP: {e}")
        return "127.0.0.1"

LOCAL_IP = get_local_ip()
print(f"[*] Server running on local IP: {LOCAL_IP}")

SERVER_EXECUTABLE_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "WindowsServer", "TrueConspiracyServer.exe")

players = {}

TTL = 60 
PING_INTERVAL = 10

class Player:
    def __init__(self, ip, port, writer):
        self.ip = ip
        self.port = port
        self.writer = writer
        self.last_ping = time.time()
        self.state = "idle"

    def __str__(self):
        return f"{self.ip}:{self.port}"

def is_port_free(port):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        return sock.connect_ex((LOCAL_IP, port)) != 0

def get_free_port(start=7000, end=8000):
    for port in range(start, end):
        if is_port_free(port):
            return port
    raise RuntimeError("Maximum number of ports reached.")

def launch_server():
    port = get_free_port()
    cmd = [
        SERVER_EXECUTABLE_PATH,
        "GameplayScene?listen",
        f"-port={port}",
        "-log"
    ]
    subprocess.Popen(cmd)
    return LOCAL_IP, port

async def handle_client(reader, writer):
    addr = writer.get_extra_info('peername')
    ip, port = addr
    player_key = f"{ip}:{port}"

    print(f"[+] Connected : {player_key}")

    player = Player(ip, port, writer)
    players[player_key] = player

    try:
        while True:
            data = await reader.readline()
            if not data:
                break

            message = data.decode().strip().lower()
            if message == "ping":
                player.last_ping = time.time()
                player.writer.write(b"pong\n")
                await player.writer.drain()

            elif message == "matchmaking":
                player.state = "matchmaking"
                print(f"[MATCHMAKING] {player_key} is looking for a match")

            elif message == "idle":
                player.state = "idle"
                print(f"[IDLE] {player_key} is idle")

    except Exception as e:
        print(f"[ERROR] {player_key}: {e}")
    finally:
        if player_key in players:
            del players[player_key]
            print(f"[-] Disconnected : {player_key}")
        writer.close()
        await writer.wait_closed()

async def ping_checker():
    while True:
        now = time.time()
        disconnected = []
        for key, player in list(players.items()):
            if now - player.last_ping > TTL:
                print(f"[TIMEOUT] {key} lost connexion.")
                try:
                    player.writer.close()
                    await player.writer.wait_closed()
                except:
                    pass
                disconnected.append(key)

        for key in disconnected:
            del players[key]

        await asyncio.sleep(PING_INTERVAL)

async def main():
    print(SERVER_EXECUTABLE_PATH)
    server = await asyncio.start_server(handle_client, '0.0.0.0', 8888)
    print("[*] Server launched on port 8888")

    asyncio.create_task(ping_checker())
    asyncio.create_task(matchmaking_loop())

    async with server:
        await server.serve_forever()

async def matchmaking_loop():
    while True:
        matchmaking_players = [p for p in players.values() if p.state == "matchmaking"]
        while len(matchmaking_players) >= 2:
            p1 = matchmaking_players.pop(0)
            p2 = matchmaking_players.pop(0)

            try:
                ip, port = launch_server()

                # Tell each player where to connect
                msg = f"match:{ip}:{port}\n"
                for p in [p1, p2]:
                    p.writer.write(msg.encode())
                    await p.writer.drain()
                    p.state = "InGame"

                print(f"[MATCH] {p1} and {p2} -> {ip}:{port}")

            except Exception as e:
                print(f"[ERROR] Could not launch server: {e}")

        await asyncio.sleep(1)

if __name__ == '__main__':
    asyncio.run(main())