FROM stateoftheartio/qt6:6.8-gcc-aqt

USER root

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    pkg-config \
    libssl-dev \
    zlib1g-dev \
    libgflags-dev \
    libgtest-dev \
    libunwind-dev \
    libxkbcommon-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    curl \
    ca-certificates \
    libxcb-cursor0 \
    libxkbcommon-x11-0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-shape0 \
    libxcb-xinerama0 \
    libxcb-xfixes0 \
    locales \
    libpqxx-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /opt
RUN git clone --branch v1.62.0 --recurse-submodules --depth 1 --shallow-submodules https://github.com/grpc/grpc.git

WORKDIR /opt/grpc
RUN cmake -S . -B build -G Ninja \
    -DgRPC_INSTALL=ON \
    -DgRPC_BUILD_TESTS=OFF \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_INSTALL_PREFIX=/usr/local \
    -DgRPC_SSL_PROVIDER=package \
    -DgRPC_ZLIB_PROVIDER=package \
    && cmake --build build \
    && cmake --install build

RUN export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
RUN ldconfig

ENV CMAKE_GENERATOR=Ninja

WORKDIR /workspace