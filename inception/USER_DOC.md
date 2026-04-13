# User Documentation

## Services

- **NGINX**: Web server, only entry point. Handles HTTPS on port 443.
- **WordPress + php-fpm**: CMS for creating and managing website content.
- **MariaDB**: Database server storing WordPress data.

## Start and Stop

```bash
make          # Start all services
make down     # Stop all services
```

## Access

- Website: `https://kgiraud.42.fr`
- Admin panel: `https://kgiraud.42.fr/wp-admin`
- Your browser will show a security warning (self-signed certificate). Click "Advanced" then "Continue".

## Credentials

- Admin login: defined in `srcs/.env` (`WP_ADMIN_USER`)
- Admin password: stored in `secrets/credentials.txt`
- Regular user login: defined in `srcs/.env` (`WP_USER`)
- Regular user password: stored in `secrets/credentials.txt`

### Changing Credentials

1. Edit the relevant file (`srcs/.env` for usernames/emails, `secrets/credentials.txt` or `secrets/db_password.txt` for passwords).
2. Rebuild and restart the services:
   ```bash
   make re
   ```

## Check Services

```bash
docker ps    								# All 3 containers should be "Up"
curl -k https://localhost   # Should return HTML
```
