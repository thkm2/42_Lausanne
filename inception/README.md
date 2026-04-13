*This project has been created as part of the 42 curriculum by kgiraud.*

# Inception

## Description

Inception is a web infrastructure built with Docker. It sets up NGINX, WordPress + php-fpm, and MariaDB, each running in its own container. All containers are built from custom Dockerfiles using Debian Bookworm as base image. Docker is used here to isolate each service in its own container, making the stack reproducible and portable across machines.

Architecture: `Client --> NGINX --> WordPress/php-fpm --> MariaDB`

**Design choices**: Debian Bookworm over Alpine for better package compatibility. Docker secrets (file-mounted) over environment variables for sensitive data. MariaDB initialized with `--init-file` instead of a background server approach.

## Instructions

Prerequisites: Docker, Docker Compose v2, Make, Git, OpenSSL.

```bash
make          # Build and start all containers
make down     # Stop and remove containers
make clean    # Stop + remove volumes and images
make fclean   # Full cleanup
make re       # fclean + make
```

Access the site at `https://<domain>` (port 443).

## Comparisons

**VM vs Docker**: A VM emulates a full machine with its own kernel. A Docker container shares the host kernel and only isolates the filesystem and processes. Containers are lighter and faster to start.

**Secrets vs Environment Variables**: Environment variables are visible with `docker inspect` or `env`. Secrets are mounted as files in `/run/secrets/`, only accessible from inside the container. Secrets are safer for passwords.

**Docker Network vs Host Network**: With host networking, the container shares the host's network stack directly — no isolation, ports conflict with host services. A Docker bridge network creates an isolated virtual network where containers communicate by service name through Docker's internal DNS. This project uses a bridge network for isolation and inter-container communication.

**Docker Volumes vs Bind Mounts**: Volumes are managed by Docker and stored in Docker's internal storage. Bind mounts map a specific host directory into the container. Volumes are portable, bind mounts give direct access to host files.

## Resources

- [Docker documentation](https://docs.docker.com/)
- [Dockerfile best practices](https://docs.docker.com/build/building/best-practices/)
- [NGINX documentation](https://nginx.org/en/docs/)
- [WordPress CLI documentation](https://developer.wordpress.org/cli/commands/)
- [MariaDB knowledge base](https://mariadb.com/kb/)

**AI usage**: Claude Code was used to research documentation and explore technical concepts.
