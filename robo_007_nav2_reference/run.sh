
if [ -z "$1" ]; then
    echo "Please provide a docker compose file number prefix (001, or 002 or 003 etc)"
    exit 1
fi

DOCKER_COMPOSE_FILE=$(find . -name "$1*.yml" | head -n 1)

if [ -z "$DOCKER_COMPOSE_FILE" ]; then
    echo "No docker compose file found starting with $1"
    exit 1
fi

echo "Starting docker compose file $DOCKER_COMPOSE_FILE"

docker compose -f $DOCKER_COMPOSE_FILE build 
docker compose -f $DOCKER_COMPOSE_FILE up   --remove-orphans 