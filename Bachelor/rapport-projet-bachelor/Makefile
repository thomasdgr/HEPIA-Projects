OPTIONS = --from markdown+footnotes
# OPTIONS += --filter=pandoc-crossref

PDFOPTIONS = --highlight-style kate
PDFOPTIONS += --lua-filter=meta-vars.lua
PDFOPTIONS += --pdf-engine xelatex
PDFOPTIONS += --template=./templates/default.latex
PDFOPTIONS += --top-level-division=chapter
PDFOPTIONS += --citeproc # Si votre Pandoc râle, remplacez "--filter pandoc-citeproc" par "--citeproc". Ou le contraire.

MD=$(sort $(wildcard text/*.md))
PDF=$(patsubst %.md,%.pdf,$(MD))
TEX=$(patsubst %.md,%.tex,$(MD))

all: rapport.pdf

rapport.pdf: rapport.tex
	xelatex --shell-escape $^
	xelatex --shell-escape $^
	xelatex --shell-escape $^
	xelatex --shell-escape $^ # Sigh. LaTeX a besoin d'être lancé plusieurs fois pour bien marcher.

rapport.tex: config.yaml $(MD)
	pandoc -s $(OPTIONS) $(PDFOPTIONS) $^ -o $@

clean:
	find . -name 'rapport.*' -not -name "rapport.pdf" -delete
