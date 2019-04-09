## How to run

### test

用 Chrome 浏览器访问时，还会请求 `favicon.ico' 。

```
filename = public_html/
printFile name public_html/index.html
[+] Process 299 served a request of 299 bytes. Total bytes sent 299
filename = public_html/
printFile name public_html/index.html
[+] Process 299 served a request of 598 bytes. Total bytes sent 299
filename = public_html/favicon.ico
printFile name 404.html
[+] Process 301 served a request of 899 bytes. Total bytes sent 301
filename = public_html/1
printFile name 404.html
[+] Process 301 served a request of 1200 bytes. Total bytes sent 301
filename = public_html/a
printFile name 404.html
[+] Process 301 served a request of 1501 bytes. Total bytes sent 301
filename = public_html/sd.html
printFile name 404.html
[+] Process 301 served a request of 1802 bytes. Total bytes sent 301
filename = public_html/../html
printFile name 400.html
[+] Process 302 served a request of 2104 bytes. Total bytes sent 302
^C[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
[+] Cleaning up connections and exiting.
```
