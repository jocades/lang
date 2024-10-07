docker build -t asmbox .

docker run --rm -it \
    -v "$(pwd):/home/jordi/app" \
    --name asm-test \
    --platform linux/arm64 \
    asmbox
