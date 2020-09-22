/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i sekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/

      N       brute       sortering
 ----------------------------------
    150       0.026           0.012
    200       0.065           0.020
    300      0.209            0.047
    400      0.455            0.082
    800      3.605            0.334
   1600      29.587           1.319
   3200      error(300)       5.592
   6400      error(3000)      22.429
  12800      error(30000)     93.907


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(n^4), eftersom vi kan räkna bort konstanterna utförs varje loop 4 gånger och vi får därför tidskomplexiteten n*n*n*n=n^4=O(n^4). Eftersom den innersta loopen oftast kommer utgå blir den genomsnittliga komplexiteten O(n^3)

Sortering:
O(n^2) eftersom vi först loopar igenom varje punkt en gång och sen jämför denna med n (konstanten utgår) andra punkter. Övriga operationer utgår eftersom de ger en mindre tidskomplexitet än O(n^2). T.ex. sorteringen av punkterna ger tidskomplexiteten O(n log(n)) men utgår p.g.a. tidigare nämnd anledning.
