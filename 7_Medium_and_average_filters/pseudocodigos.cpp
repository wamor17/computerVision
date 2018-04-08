para i=0 hasta rows
para j=0 hasta cols
	sum=0; mi=0;
	para ni=i-N hasta i+N
		mj=0;
		para nj=j-N hasta j+N
			suma += mask(mi,mj)*image(ni, nj);
			mj++;
		fin para
		mi++;
	fin para	
	imageOut(i,j) = redondea(suma/(NumElementos))
fin para
fin para


para i=0 hasta rows
para j=0 hasta cols
	m=0; mi=0;
	para ni=i-N hasta i+N
		mj=0;
		para nj=j-N hasta j+N
			arregloVecindad[m] = mask(mi,mj)*image(ni, nj);
			mj++; m++;
		fin para
		mi++;
	fin para	
	imageOut(i,j) = funcionMediana(arregloVecindad, pixelesFiltro);
fin para
fin para
