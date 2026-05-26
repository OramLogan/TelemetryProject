FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    make \
    git \
    python3 \
    libasio-dev \
    pkg-config \
    libpqxx-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN mkdir -p build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

EXPOSE 8080

CMD ["./build/telemetry_app"]