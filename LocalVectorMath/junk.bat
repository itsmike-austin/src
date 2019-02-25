mt -manifest AdvancedAlignedVector.dll.manifest AdvancedUnalignedVector.dll.manifest -identity:"Its.Vector, processorArchitecture=x86, version=1.2.0.0" -makecdfs -out:junk.manifest
makecat junk.manifest.cdf
mt -manifest junk.manifest -hashupdate -makecdfs

3eb39869230f0da5"