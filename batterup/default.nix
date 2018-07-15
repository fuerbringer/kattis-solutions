{ mkDerivation, base, split, stdenv }:
mkDerivation {
  pname = "batterup";
  version = "0.1.0.0";
  src = ./.;
  isLibrary = false;
  isExecutable = true;
  executableHaskellDepends = [ base split ];
  license = stdenv.lib.licenses.gpl3;
}
