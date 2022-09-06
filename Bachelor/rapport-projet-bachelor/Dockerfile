FROM pandoc/latex

RUN apk update && apk add bash make

RUN tlmgr update --self
RUN tlmgr install \
      sectsty \
      enumitem \
      glossaries \
      wrapfig \
      mfirstuc \
      textcase \
      xfor \
      tracklang \
      datatool \
      tocbibind \
      titlesec \
      background \
      textpos \
      tocloft \
      svg \
      everypage \
      trimspaces \
      catchfile \
      koma-script \
      transparent \
      pdfpages

ENTRYPOINT ["/bin/bash", "-l", "-c"]
WORKDIR /build