# Developer Documentation

## Prerequisites

- A **Debian virtual machine** with the following installed:
  - Docker and Docker Compose v2 (`docker compose version`)
  - Make
  - Git

## Setup

1. Clone the repository
2. Create `secrets/` directory with one value per file, no trailing newline:
   - `credentials.txt` — password shared by WordPress admin and regular user
   - `db_password.txt` — MariaDB user password
   - `db_root_password.txt` — MariaDB root password
3. Configure `srcs/.env`:
   | Variable | Description |
   |---|---|
   | `DOMAIN_NAME` | Your domain (`<login>.42.fr`) |
   | `MYSQL_DATABASE` | Database name (e.g. `wordpress`) |
   | `MYSQL_USER` | MariaDB user (non-root) |
   | `WP_ADMIN_USER` | WordPress admin — must **not** contain `admin` |
   | `WP_ADMIN_EMAIL` | WordPress admin email |
   | `WP_USER` | WordPress regular user |
   | `WP_USER_EMAIL` | WordPress regular user email |

## Build and Launch

```bash
make          # Create volume directories on host, build images, start containers
make down     # Stop containers
make clean    # Stop + remove volumes and images
make fclean   # Full cleanup (containers, volumes, images, host data dirs)
make re       # fclean + make
```

## Useful Commands

```bash
docker ps                              # Container status
docker logs <container_name>           # View logs
docker exec -it <container_name> bash  # Enter a container
docker volume ls                       # List volumes
docker network ls  										 # List networks
```

**Inside MariaDB container** (useful for eval):
```bash
mysql -u <MYSQL_USER> -p <MYSQL_DATABASE>
SHOW DATABASES;                        # List databases
SHOW TABLES;                           # List tables in current DB
SELECT * FROM wp_users;                # Check WordPress users
```

## Data Persistence

- **MariaDB data**: stored in the `db_data` Docker volume, mapped to `/var/lib/mysql` in the container
- **WordPress files**: stored in the `wp_data` Docker volume, mapped to `/var/www/html` in the container
- Data survives `make down`. Only `make clean` or `make fclean` removes volumes.

## Project Structure

```
srcs/requirements/mariadb/    # MariaDB: Dockerfile, config (50-server.cnf), init script
srcs/requirements/wordpress/  # WordPress: Dockerfile, config (www.conf), init script
srcs/requirements/nginx/      # NGINX: Dockerfile, config (nginx.conf), init script
srcs/docker-compose.yml       # Orchestrates all 3 services
srcs/.env                     # Environment variables (not in git)
secrets/                      # Passwords (not in git)
```
