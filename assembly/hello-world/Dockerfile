FROM --platform=linux/arm64 alpine:latest

# Install zsh and other useful tools
RUN apk add --no-cache \
    gcc \
    clang \
    make \
    musl-dev \
    gdb \
    zsh


# Create a non-root user
RUN adduser -D jordi
USER jordi
WORKDIR /home/jordi

# Set zsh as the default shell
SHELL ["/bin/zsh", "-c"]

# Set the default command to zsh
CMD ["/bin/zsh"]
