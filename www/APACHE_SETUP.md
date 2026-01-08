# Apache Configuration for Riau

## Option 1: .htaccess (Recommended for shared hosting)

Create `.htaccess` in your web root:

```apache
# Enable CGI execution
Options +ExecCGI

# Add .riau handler
AddHandler cgi-script .riau

# Optional: Set index.riau as directory index
DirectoryIndex index.riau index.html

# Optional: Error pages
ErrorDocument 404 /404.riau
ErrorDocument 500 /500.riau
```

## Option 2: httpd.conf (For dedicated servers)

Add to your Apache configuration:

```apache
<Directory "/var/www/html">
    Options +ExecCGI
    AddHandler cgi-script .riau
    AllowOverride All
    Require all granted
</Directory>

# Set .riau as valid index
<IfModule dir_module>
    DirectoryIndex index.riau index.html
</IfModule>
```

## Complete Virtual Host Example

```apache
<VirtualHost *:80>
    ServerName riau-app.local
    DocumentRoot "/var/www/riau-app"
    
    <Directory "/var/www/riau-app">
        Options +ExecCGI
        AddHandler cgi-script .riau
        AllowOverride All
        Require all granted
        DirectoryIndex index.riau
    </Directory>
    
    ErrorLog ${APACHE_LOG_DIR}/riau-error.log
    CustomLog ${APACHE_LOG_DIR}/riau-access.log combined
</VirtualHost>
```

## Setup Steps

### 1. Install Apache

**Ubuntu/Debian**:
```bash
sudo apt update
sudo apt install apache2
```

**CentOS/RHEL**:
```bash
sudo yum install httpd
```

### 2. Enable CGI Module

```bash
sudo a2enmod cgi
sudo systemctl restart apache2
```

### 3. Deploy Riau Files

```bash
# Copy www folder to web root
sudo cp -r www/* /var/www/html/

# Make scripts executable
sudo chmod +x /var/www/html/*.riau
sudo chmod +x /var/www/html/api/*.riau

# Set ownership
sudo chown -R www-data:www-data /var/www/html/
```

### 4. Create .htaccess

```bash
sudo nano /var/www/html/.htaccess
```

Add:
```apache
Options +ExecCGI
AddHandler cgi-script .riau
DirectoryIndex index.riau
```

### 5. Restart Apache

```bash
sudo systemctl restart apache2
```

### 6. Test

Visit: `http://localhost/index.riau`

## Troubleshooting

### "Forbidden" Error
```bash
# Check permissions
ls -la /var/www/html/*.riau

# Should show: -rwxr-xr-x

# Fix if needed
chmod +x /var/www/html/*.riau
```

### "Internal Server Error"
```bash
# Check Apache error log
sudo tail -f /var/log/apache2/error.log

# Common issues:
# 1. Missing shebang: #!/usr/bin/env riau
# 2. riau not in PATH
# 3. Wrong permissions
```

### CGI Not Enabled
```bash
# Enable CGI module
sudo a2enmod cgi
sudo systemctl restart apache2
```

---

**Ready!** Your Riau application should now work exactly like PHP! 🚀
