FROM alpine:latest
LABEL maintainer="Yoda"
ADD files.tar.gz /dir_tar
RUN mkdir /dir_add
COPY file0* /dir_add/
CMD ["ls", "-al", "/dir_tar", "/dir_add"]
