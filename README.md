# hacksim

A console "hacker terminal" simulator in C++, in the style of *Mr. Robot* / Kali Linux.
Everything is **simulated**: the program performs no network operations or attacks; it only generates realistic-looking output.

## Commands (selection)

| Area | Commands |
|---|---|
| Basics | `help`, `clear`, `exit` / `quit`, `history` |
| Recon | `nmap <target>`, `whois <domain>`, `dig <domain>`, `traceroute <ip>` |
| Exploitation | `msfconsole`, `use exploit/<name>`, `set TARGET <ip>`, `set PAYLOAD <payload>`, `exploit` / `run`, `sessions` |
| Cracking | `hydra <target> <service>`, `john <hashfile>`, `hashcat <hash>` |
| Network | `ifconfig` / `ip a`, `netstat`, `tcpdump`, `arpspoof <target>`, `ssh <user>@<host>`, `scp <file> <target>` |
| System | `whoami`, `id`, `uname -a`, `ps aux`, `top` / `htop`, `ls` / `cat` / `cd`, `chmod` / `chown`, `crontab`, `grep` |

Plus scrolling system logs, animated load bars and progress animations. Full list (in Polish): [REQUIREMENTS.md](REQUIREMENTS.md).

## Build

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/hacksim
```

## License

MIT — see [LICENSE](LICENSE).
