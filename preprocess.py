from pathlib import Path
from argparse import ArgumentParser

def preprocess(book, file, local=True):
	book_files = {f.stem: f for f in book.glob("**/*.hpp")}
	included = set()

	def prep_file(filename):
		nonlocal included
		if filename in included: return
		included.add(filename)

		if local: print(f'#line 1 "{filename}"')
		for i, line in enumerate(open(filename)):
			s = line.strip()
			if s.startswith('//$ locally require') and local: files = s.split()[3:]
			elif s.startswith('//$ require'): files = s.split()[2:]
			elif s.startswith('///') or s.startswith('//$'): files = []
			else:
				print(line, end='\n' if not line.endswith('\n') else '')
				continue
			for f in files: prep_file(book_files[f])
			if local: print(f'#line {i+2} "{filename}"')

	prep_file(file)

if __name__ == '__main__':
	parser = ArgumentParser()
	parser.add_argument('--local', action='store_true')
	parser.add_argument('book', type=Path)
	parser.add_argument('file', type=Path)
	args = parser.parse_args()
	preprocess(args.book, args.file, args.local)
