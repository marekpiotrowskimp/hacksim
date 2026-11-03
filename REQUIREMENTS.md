# Wymagania projektu

## Opis projektu
Aplikacja konsolowa symulująca realistyczny terminal hakerski w stylu Kali Linux / Mr. Robot.
Użytkownik może wpisywać komendy i obserwować realistyczne wizualizacje:
- output w stylu prawdziwych narzędzi pentestingowych (nmap, metasploit, hydra)
- logi systemowe przewijające się w tle
- słupkowe wykresy obciążenia systemu
- wyszukiwanie i eksfiltracja danych
- symulacja exploitów i payload'ów

Inspiracje:
- Serial "Mr. Robot" (realistyczne hacki Elliota)
- Kali Linux i narzędzia: nmap, metasploit, hydra, john, aircrack-ng
- Estetyka: minimalistyczna, profesjonalna, zielony/czerwony tekst na czarnym tle

Cel: poczuć się jak Elliot Alderson - prawdziwy haker, nie hollywoodzki.

## Wymagania funkcjonalne

### Komendy podstawowe
1. `help` - wyświetla listę dostępnych komend
2. `clear` - czyści ekran
3. `exit` / `quit` - wyjście z programu

### Rekonesans (styl nmap/recon)
4. `nmap <target>` - symulacja skanowania portów z realistycznym outputem
5. `whois <domain>` - symulowane dane rejestracji domeny
6. `dig <domain>` - symulacja DNS lookup
7. `traceroute <ip>` - śledzenie trasy pakietów przez węzły

### Eksploitacja (styl metasploit)
8. `msfconsole` - uruchomienie "metasploit" z bannerem
9. `use exploit/<nazwa>` - wybór exploita
10. `set TARGET <ip>` - ustawienie celu
11. `set PAYLOAD <payload>` - wybór payloadu
12. `exploit` / `run` - uruchomienie ataku z animacją
13. `sessions` - lista aktywnych "sesji"

### Łamanie haseł (styl hydra/john)
14. `hydra <target> <service>` - brute-force z przewijającą się listą prób
15. `john <hashfile>` - łamanie hashy z progress barem
16. `hashcat <hash>` - symulacja GPU crackingu

### Sieć i sniffing
17. `ifconfig` / `ip a` - konfiguracja sieci
18. `netstat` - aktywne połączenia
19. `tcpdump` - przechwytywanie pakietów (scrollujące się dane)
20. `arpspoof <target>` - symulacja ARP spoofing

### System (symulowane)
21. `whoami` - aktualny "użytkownik"
22. `id` - informacje o użytkowniku
23. `uname -a` - info o systemie
24. `ps aux` - lista procesów
25. `top` / `htop` - monitor zasobów z animowanymi słupkami
26. `ls` / `cat` / `cd` - nawigacja po "systemie plików"

### Zaawansowane
27. `ssh <user>@<host>` - symulacja połączenia SSH
28. `scp <file> <target>` - transfer plików
29. `chmod` / `chown` - zmiana uprawnień
30. `crontab` - zaplanowane zadania
31. `history` - historia komend
32. `grep <pattern> <file>` - wyszukiwanie w plikach

## Wymagania niefunkcjonalne
1. **Responsywny interfejs** - automatyczne dostosowanie do rozmiaru terminala (jak opencode)
   - Dynamiczne przeliczanie layoutu przy resize
   - Nasłuchiwanie sygnału SIGWINCH (zmiana rozmiaru okna)
   - Minimalne wymagania: 80x24 znaków
   - Graceful degradation przy małych oknach
2. Płynne animacje (min. 30 FPS dla efektów)
3. Kolorowy output (ANSI escape codes przez FTXUI)
4. Responsywny input - program nie może się zawieszać podczas animacji
5. Działa na Linux/macOS/Windows (cross-platform)
6. Mały rozmiar binarki (<5MB)
7. Brak zewnętrznych zależności runtime (statyczne linkowanie)

## Technologie
- **Język:** C++17 (lub nowszy)
- **Biblioteka UI:** FTXUI (modern terminal UI)
- **Build system:** CMake
- **Kolory:** ANSI escape codes (przez FTXUI)
- **Kompilator:** clang++ (macOS) / g++ (Linux) / MSVC (Windows)

## Interfejs użytkownika (CLI)

### Wygląd promptu (styl Kali/Mr. Robot)
```
root@kali:~# _
```
lub po "przejęciu" systemu:
```
root@EVILCORP-PC:/home/admin# _
```
lub styl Elliota:
```
elliot@fsociety:~/workspace$ _
```

### Elementy wizualne
- Minimalistyczna kolorystyka (zielony, czerwony, biały na czarnym tle)
- Realistyczny output narzędzi (nmap, metasploit, hydra)
- Paski postępu przy długich operacjach
- Scrollujące się logi i dane pakietów
- Animowany `htop` z wykresami CPU/RAM
- Bannery ASCII narzędzi (metasploit, hydra)
- Realistyczne komunikaty błędów i ostrzeżeń
- Timestamp przy logach [2024-01-15 03:42:17]

## Priorytetyzacja

### Wysoki priorytet (MVP)
- Podstawowa pętla komend (input -> reakcja)
- Prompt w stylu Kali Linux
- `help`, `clear`, `exit`, `whoami`, `id`, `uname`
- `nmap` - realistyczny output skanowania portów
- `ls`, `cat`, `cd` - nawigacja po symulowanym systemie plików
- `ps aux` - lista procesów
- Kolorowy output (zielony/czerwony/biały)

### Średni priorytet
- `msfconsole` z bannerem i podstawowymi komendami
- `hydra` - animacja brute-force
- `htop` - monitor zasobów z animacją
- `ssh` - symulacja połączenia
- `tcpdump` - scrollujące się pakiety
- `netstat`, `ifconfig`
- Symulowany system plików z "tajnymi" danymi

### Niski priorytet
- `john`, `hashcat` - łamanie hashy
- `arpspoof`, `traceroute`
- `scp`, `chmod`, `chown`, `crontab`
- Wiele "przejętych" sesji
- Scenariusze/misje do wykonania
- Easter eggs (fsociety, E Corp, itp.)
