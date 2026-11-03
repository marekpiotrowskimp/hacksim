# hacksim

Konsolowy symulator „terminala hakera” w stylu *Mr. Robot* / Kali Linux, napisany w C++.
Wszystko jest **symulacją**: program nie wykonuje żadnych operacji sieciowych ani ataków, generuje tylko realistycznie wyglądający output.

- komendy w stylu `nmap`, `whois`, `dig`, `traceroute`, `msfconsole`, `hydra`, `john`, `aircrack-ng`
- przewijające się logi systemowe, wykresy obciążenia, animacje

Pełna lista komend: [REQUIREMENTS.md](REQUIREMENTS.md).

## Build

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/hacksim
```
