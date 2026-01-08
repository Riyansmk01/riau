# Nginx Configuration for Riau

## nginx.conf Configuration

Add to your Nginx configuration:

```nginx
server {
    listen 80;
    server_name riau-app.local;
    root /var/www/riau-app;
    index index.riau index.html;

    # Handle .riau files via CGI
    location ~ \.riau$ {
        gzip off;
        root /var/www/riau-app;
        fastcgi_pass unix:/var/run/fcgiwrap.socket;
        include fastcgi_params;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        fastcgi_param DOCUMENT_ROOT $document_root;
    }

    # Static files
    location / {
        try_files $uri $uri/ =404;
    }

    # Logs
    access_log /var/log/nginx/riau-access.log;
    error_log /var/log/nginx/riau-error.log;
}
```

## Setup Steps

### 1. Install Nginx

**Ubuntu/Debian**:
```bash
sudo apt update
sudo apt install nginx
```

**CentOS/RHEL**:
```bash
sudo yum install nginx
```

### 2. Install fcgiwrap (CGI wrapper)

**Ubuntu/Debian**:
```bash
sudo apt install fcgiwrap
```

**CentOS/RHEL**:
```bash
sudo yum install fcgiwrap
```

### 3. Deploy Riau Files

```bash
# Create directory
sudo mkdir -p /var/www/riau-app

# Copy files
sudo cp -r www/* /var/www/riau-app/

# Make executable
sudo chmod +x /var/www/riau-app/*.riau
sudo chmod +x /var/www/riau-app/api/*.riau

# Set ownership
sudo chown -R www-data:www-data /var/www/riau-app/
```

### 4. Create Nginx Site Config

```bash
sudo nano /etc/nginx/sites-available/riau-app
```

Add the configuration above.

### 5. Enable Site

```bash
sudo ln -s /etc/nginx/sites-available/riau-app /etc/nginx/sites-enabled/
sudo nginx -t
sudo systemctl restart nginx
```

### 6. Start fcgiwrap

```bash
sudo systemctl enable fcgiwrap
sudo systemctl start fcgiwrap
```

### 7. Test

Visit: `http://localhost/index.riau`

## Alternative: Without fcgiwrap (Direct CGI)

If you want simpler setup without fcgiwrap:

```nginx
location ~ \.riau$ {
    gzip off;
    root /var/www/riau-app;
    
    # Execute directly
    fastcgi_pass 127.0.0.1:9000;
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
}
```

Then run riau-fpm (when available in v0.3.0).

## Troubleshooting

### "502 Bad Gateway"
```bash
# Check fcgiwrap status
sudo systemctl status fcgiwrap

# Check socket exists
ls -la /var/run/fcgiwrap.socket

# Restart if needed
sudo systemctl restart fcgiwrap
```

### "Permission Denied"
```bash
# Check file permissions
ls -la /var/www/riau-app/*.riau

# Fix permissions
sudo chmod +x /var/www/riau-app/*.riau
sudo chown -R www-data:www-data /var/www/riau-app/
```

### "File Not Found"
```bash
# Check Nginx error log
sudo tail -f /var/log/nginx/riau-error.log

# Verify paths in config
# Ensure SCRIPT_FILENAME is correct
```

## Performance Tuning

```nginx
# Add to server block
location ~ \.riau$ {
    # ... existing config ...
    
    # Increase timeouts for long-running scripts
    fastcgi_read_timeout 300;
    fastcgi_send_timeout 300;
    
    # Buffer settings
    fastcgi_buffer_size 128k;
    fastcgi_buffers 4 256k;
    fastcgi_busy_buffers_size 256k;
}
```

---

**Ready!** Your Riau application is now running on Nginx! 🚀
