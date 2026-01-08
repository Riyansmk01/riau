# Membuat index.riau - Panduan Lengkap

## 🎯 Quick Start (5 Menit)

### 1. Template Dasar index.riau

```riau
#!/usr/bin/env riau
// WAJIB: Content-Type header
print("Content-Type: text/html; charset=UTF-8\n\n")

// HTML Output
print("<!DOCTYPE html>")
print("<html lang='id'>")
print("<head>")
print("    <meta charset='UTF-8'>")
print("    <meta name='viewport' content='width=device-width, initial-scale=1.0'>")
print("    <title>Halaman Riau Saya</title>")
print("</head>")
print("<body>")
print("    <h1>Hello dari Riau!</h1>")
print("    <p>Ini adalah halaman web pertama saya dengan Riau.</p>")
print("</body>")
print("</html>")
```

### 2. Simpan sebagai `index.riau`

```bash
# Buat file
notepad index.riau

# Atau dengan echo (Windows PowerShell)
@"
#!/usr/bin/env riau
print("Content-Type: text/html\n\n")
print("<h1>Hello Riau!</h1>")
"@ | Out-File -Encoding UTF8 index.riau
```

### 3. Test Lokal

```bash
# Test langsung
riau index.riau

# Output akan muncul di terminal
```

---

## 🌐 Deploy ke Web Server

### Opsi 1: Apache (Paling Mudah)

#### A. Buat `.htaccess`

```apache
# .htaccess
Options +ExecCGI
AddHandler cgi-script .riau
DirectoryIndex index.riau index.html
```

#### B. Struktur Folder

```
C:\xampp\htdocs\myproject\
├── .htaccess
├── index.riau
├── about.riau
└── api\
    └── users.riau
```

#### C. Akses di Browser

```
http://localhost/myproject/
```

### Opsi 2: Nginx

#### A. Config Nginx

```nginx
location ~ \.riau$ {
    gzip off;
    root /var/www/html;
    fastcgi_pass unix:/var/run/fcgiwrap.socket;
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
}
```

#### B. Install fcgiwrap

```bash
sudo apt install fcgiwrap
sudo systemctl start fcgiwrap
```

---

## 📝 Template Lengkap dengan Fitur

### Template 1: Homepage dengan CSS

```riau
#!/usr/bin/env riau
print("Content-Type: text/html; charset=UTF-8\n\n")

print("<!DOCTYPE html>")
print("<html lang='id'>")
print("<head>")
print("    <meta charset='UTF-8'>")
print("    <title>Beranda - Riau App</title>")
print("    <style>")
print("        * { margin: 0; padding: 0; box-sizing: border-box; }")
print("        body { font-family: Arial, sans-serif; background: #f5f5f5; }")
print("        .container { max-width: 800px; margin: 50px auto; padding: 20px; background: white; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }")
print("        h1 { color: #333; margin-bottom: 20px; }")
print("        p { color: #666; line-height: 1.6; }")
print("    </style>")
print("</head>")
print("<body>")
print("    <div class='container'>")
print("        <h1>Selamat Datang di Riau!</h1>")
print("        <p>Ini adalah aplikasi web yang dibuat dengan bahasa pemrograman Riau.</p>")
print("    </div>")
print("</body>")
print("</html>")
```

### Template 2: Dengan Environment Variables

```riau
#!/usr/bin/env riau
print("Content-Type: text/html; charset=UTF-8\n\n")

// Ambil data dari environment
let method = env("REQUEST_METHOD")
let query = env("QUERY_STRING")
let userAgent = env("HTTP_USER_AGENT")

print("<!DOCTYPE html>")
print("<html>")
print("<head><title>Server Info</title></head>")
print("<body>")
print("    <h1>Server Information</h1>")
print("    <ul>")
print("        <li>Method: " + method + "</li>")
print("        <li>Query: " + query + "</li>")
print("        <li>User Agent: " + userAgent + "</li>")
print("    </ul>")
print("</body>")
print("</html>")
```

### Template 3: API JSON

```riau
#!/usr/bin/env riau
print("Content-Type: application/json; charset=UTF-8\n\n")

print("{")
print("  \"status\": \"success\",")
print("  \"message\": \"Hello from Riau API\",")
print("  \"data\": {")
print("    \"version\": \"0.1.1\",")
print("    \"timestamp\": \"2026-01-08\"")
print("  }")
print("}")
```

---

## 🔧 Troubleshooting

### Error: "500 Internal Server Error"

**Penyebab 1**: Tidak ada Content-Type header
```riau
// ❌ SALAH
print("<h1>Hello</h1>")

// ✅ BENAR
print("Content-Type: text/html\n\n")
print("<h1>Hello</h1>")
```

**Penyebab 2**: File tidak executable (Unix/Linux)
```bash
chmod +x index.riau
```

**Penyebab 3**: Shebang salah
```riau
#!/usr/bin/env riau  # ✅ BENAR
#!/bin/riau          # ❌ SALAH (path hardcoded)
```

### Error: "File Not Found"

**Solusi**: Pastikan `.htaccess` ada dan benar
```apache
Options +ExecCGI
AddHandler cgi-script .riau
DirectoryIndex index.riau
```

### Error: "Permission Denied"

**Windows**: Pastikan `riau.exe` ada di PATH
```powershell
# Cek PATH
$env:Path

# Tambah ke PATH jika belum
$env:Path += ";C:\Users\YourName\.riau\bin"
```

**Linux**: Pastikan file executable
```bash
ls -la index.riau
# Should show: -rwxr-xr-x

chmod +x index.riau
```

---

## 🚀 Best Practices

### 1. Selalu Gunakan Content-Type

```riau
// HTML
print("Content-Type: text/html; charset=UTF-8\n\n")

// JSON
print("Content-Type: application/json; charset=UTF-8\n\n")

// Plain Text
print("Content-Type: text/plain; charset=UTF-8\n\n")
```

### 2. Gunakan Shebang untuk Portability

```riau
#!/usr/bin/env riau
// Code here...
```

### 3. Struktur Project yang Rapi

```
myproject/
├── .htaccess           # Apache config
├── index.riau          # Homepage
├── about.riau          # About page
├── contact.riau        # Contact page
├── api/
│   ├── users.riau      # Users API
│   └── posts.riau      # Posts API
└── assets/
    ├── style.css       # CSS files
    └── script.js       # JS files
```

### 4. Error Handling

```riau
#!/usr/bin/env riau
print("Content-Type: text/html\n\n")

let user = env("USER")
if user {
    print("<p>Welcome, " + user + "!</p>")
} else {
    print("<p>Welcome, Guest!</p>")
}
```

---

## 📚 Contoh Lengkap: Blog Homepage

```riau
#!/usr/bin/env riau
print("Content-Type: text/html; charset=UTF-8\n\n")

print("<!DOCTYPE html>")
print("<html lang='id'>")
print("<head>")
print("    <meta charset='UTF-8'>")
print("    <meta name='viewport' content='width=device-width, initial-scale=1.0'>")
print("    <title>Blog Saya - Powered by Riau</title>")
print("    <style>")
print("        body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 0; padding: 0; background: #f4f4f4; }")
print("        header { background: #333; color: white; padding: 1rem; text-align: center; }")
print("        .container { max-width: 1200px; margin: 2rem auto; padding: 0 1rem; }")
print("        .post { background: white; padding: 2rem; margin-bottom: 2rem; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }")
print("        .post h2 { color: #333; margin-bottom: 0.5rem; }")
print("        .post .meta { color: #666; font-size: 0.9rem; margin-bottom: 1rem; }")
print("        .post p { color: #444; line-height: 1.6; }")
print("        footer { background: #333; color: white; text-align: center; padding: 1rem; margin-top: 2rem; }")
print("    </style>")
print("</head>")
print("<body>")
print("    <header>")
print("        <h1>Blog Saya</h1>")
print("        <p>Dibuat dengan Riau - The Best CGI Scripting Language</p>")
print("    </header>")
print("    <div class='container'>")
print("        <div class='post'>")
print("            <h2>Artikel Pertama</h2>")
print("            <div class='meta'>Ditulis pada 8 Januari 2026</div>")
print("            <p>Ini adalah artikel pertama di blog saya yang dibuat dengan Riau. Riau adalah bahasa pemrograman modern untuk CGI scripting.</p>")
print("        </div>")
print("        <div class='post'>")
print("            <h2>Kenapa Riau?</h2>")
print("            <div class='meta'>Ditulis pada 7 Januari 2026</div>")
print("            <p>Riau menggabungkan kemudahan PHP dengan keamanan modern. Null safety, enhanced error messages, dan syntax yang clean!</p>")
print("        </div>")
print("    </div>")
print("    <footer>")
print("        <p>&copy; 2026 Blog Saya. Powered by Riau v0.1.1</p>")
print("    </footer>")
print("</body>")
print("</html>")
```

---

## ✅ Checklist Deployment

- [ ] File `index.riau` dibuat dengan Content-Type header
- [ ] Shebang `#!/usr/bin/env riau` ada di baris pertama
- [ ] File `.htaccess` ada (untuk Apache)
- [ ] `riau.exe` ada di PATH
- [ ] File executable (Unix: `chmod +x`)
- [ ] Test lokal: `riau index.riau`
- [ ] Deploy ke web server
- [ ] Test di browser: `http://localhost/`

---

## 🎉 Selamat!

Sekarang Anda bisa membuat aplikasi web dengan Riau seperti PHP!

**Next Steps**:
- Buat halaman login
- Buat API endpoints
- Tambahkan database (coming in v0.3.0)
- Deploy ke production server

**Documentation**: https://github.com/Riyansmk01/riau  
**Examples**: Lihat folder `www/` di repository
