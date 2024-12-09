# Используем чистый образ Ubuntu
FROM ubuntu:latest

# Устанавливаем зависимости
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    libsubunit-dev \
    valgrind \
    vim \
    cmake \
    git \
    clang \
    llvm \
    lcov \
    clang-format \
    libpcre3 \
    libpcre3-dev \
    build-essential \
    && apt-get clean

# Скачиваем и устанавливаем Google Test
RUN git clone https://github.com/google/googletest.git /googletest && \
    cd /googletest && \
    cmake -S . -B build && \
    cmake --build build && \
    cmake --install build

# Копируем исходный код в контейнер
COPY . /code

# Устанавливаем рабочую директорию
WORKDIR /code

# Устанавливаем команду по умолчанию
CMD ["/bin/bash"]
