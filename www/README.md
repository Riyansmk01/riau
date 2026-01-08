# Riau Demo Web Application

This is a complete demo showing Riau working **exactly like PHP**.

## 📁 Structure

```
www/
├── index.riau          # Homepage
├── login.riau          # Login form
├── form.riau           # Form handler
├── about.riau          # About page
├── api/
│   └── users.riau      # JSON API endpoint
├── .htaccess           # Apache config
├── APACHE_SETUP.md     # Apache guide
├── NGINX_SETUP.md      # Nginx guide
└── README.md           # This file
```

## 🚀 Quick Start

### Option 1: Local Testing (No Web Server)

```bash
# Run directly
riau index.riau
riau login.riau
riau api/users.riau
```

### Option 2: Apache

1. Copy `www/` to `/var/www/html/`
2. Follow `APACHE_SETUP.md`
3. Visit `http://localhost/index.riau`

### Option 3: Nginx

1. Copy `www/` to `/var/www/riau-app/`
2. Follow `NGINX_SETUP.md`
3. Visit `http://localhost/index.riau`

## 📄 Pages

### index.riau
- Homepage with server info
- Links to all pages
- Beautiful modern UI

### login.riau
- Login form (GET method for demo)
- Redirects to form.riau

### form.riau
- Form handler
- Shows query string data
- Success message

### api/users.riau
- JSON API endpoint
- Returns user data
- Includes metadata

### about.riau
- About Riau
- Feature list
- Version info

## 🎯 Key Features Demonstrated

✅ **CGI Execution** - Like PHP  
✅ **Environment Variables** - `env()` function  
✅ **Dynamic HTML** - Generated on-the-fly  
✅ **JSON API** - REST endpoint  
✅ **Form Handling** - Query string parsing  
✅ **Modern UI** - Beautiful design  
✅ **Shebang Support** - `#!/usr/bin/env riau`  

## 🔧 Requirements

- Riau 0.1.1+
- Apache or Nginx
- fcgiwrap (for Nginx)

## 📝 Notes

### This is NOT PHP, but feels like it!

**Similarities**:
- Drop file & run
- CGI execution
- Environment variables
- No compilation needed

**Differences (Better!)**:
- Null safety
- Enhanced error messages
- Modern syntax
- Type inference

## 🎨 Customization

All files are standalone. Edit any `.riau` file to customize:

```riau
print("Content-Type: text/html\n\n")
print("<h1>Your Custom Page</h1>")
```

## 🐛 Troubleshooting

### "Permission Denied"
```bash
chmod +x *.riau
chmod +x api/*.riau
```

### "Internal Server Error"
- Check shebang: `#!/usr/bin/env riau`
- Verify `riau` is in PATH
- Check web server error logs

### "File Not Found"
- Verify file permissions
- Check web server config
- Ensure CGI is enabled

## 📚 Learn More

- [GUIDE.md](../GUIDE.md) - Complete documentation
- [APACHE_SETUP.md](APACHE_SETUP.md) - Apache setup
- [NGINX_SETUP.md](NGINX_SETUP.md) - Nginx setup

---

**Enjoy building with Riau!** 🚀

*The Best CGI Scripting Language*
