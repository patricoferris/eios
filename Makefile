.PHONEY: build
build:
				dune build --profile release

# REPLACE app id for whatever device you want ``
.PHONEY: sim
sim:
				# xcrun simctl boot 380020AA-7DCC-41DE-AF45-239CA5C6FA3D
				xcrun simctl spawn 380020AA-7DCC-41DE-AF45-239CA5C6FA3D _build/ios/src/main.exe --console-pty