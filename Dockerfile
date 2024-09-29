FROM debian:latest
LABEL AUTHOR "Brian Salehi <briansalehi@proton.me>"
LABEL VERSION "0.6"
LABEL DESCRIPTION "Technical References Training Program"

RUN apt update && apt upgrade --yes && apt install --yes --no-install-recommends build-essential binutils software-properties-common ca-certificates wget curl bash make gcc g++ git

# install latest cmake
RUN bash -c "git clone https://github.com/kitware/cmake.git /usr/src/cmake && cd /usr/src/cmake && git checkout $("${prefix_path}/bin/cmake" --version | sed -En 's/.*[^0-9](([0-9]+\.){2}[0-9]+).*/\1/p;q') && ./bootstrap && ./configure && make -j8 && make install"

# install postgres
RUN git clone https://github.com/theory/pgenv.git /usr/src/pgenv
RUN ln -s /usr/src/pgenv/bin/pgenv /usr/bin/pgenv
RUN pgenv use 16.4

# import database
RUN git clone https://github.com/briansalehi/references.git /usr/src/references
RUN psql -U postgres -c "create schema flashback with login;"
RUN psql -U postgres -c "create database flashback owner flashback;"
RUN psql -U flashback -f /usr/src/references/flashback.sql

# install project
RUN git clone https://github.com/briansalehi/milestone.git /usr/src/milestone
RUN cmake -S /usr/src/milestone -B /tmp/milestone-release -D CMAKE_BUILD_TYPE=Release
RUN cmake --build /tmp/milestone-release --parallel 8 --config Release --target all
RUN cmake --install /tmp/milestone-release

CMD flashback version
