# Lab esperienza 1

![diagram](./diagram.svg)

- FILE NAME: LYSO3.dst ID 300
- FILE NAME: LYSO4.dst ID 400

Misurazione di 200 keV o 300 keV e decadimento beta dentro il LYSO

## Oscilloscope channels

- Channel 1 LYSO no amplification
- Channel 2 LYSO amplified 
- Channel 3 NaI 1
- Channel 4 NaI 2


## Oscilloscope settings


| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |   -3 mV    |
|     3    |   10 mV   | NegEdge   |   -3 mV    |
|     4    |   10 mV   | NegEdge   |   -3 mV    |

Trigger pattern = AND

--------------------------------------------------------------


- FILE NAME Co2_1.dst ID 400

Calibrazione degli scintillatori NaI con sorgente Co 60

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   2 mV    | NegEdge   |   -2 mV    | (Veto)
|     3    |   50 mV   | NegEdge   |    -5 mV   |
|     4    |   50 mV   | NegEdge   |    -5 mV   |

Trigger Pattern (~no.2 ) & (no. 3) & (no. 4)


-------------------------------------------------------

- FILE NAME: Co2_2.dst ID 500

Calibrazione del cristallo di LYSO con sorgente C0 60

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -15 mV  |
|     3    |   10 mV   | No        |    -5 mV   | (Veto)
|     4    |   50 mV   | NegEdge   |    -33 mV  |

Trigger	Pattern	(no.2 ) & (~no. 3) & (no. 4)


-----------------------------------------------

- FILE NAME: Na2_1.dst

Calibrazione con sorgente Na22
LYSO deve vedere 1200 keV
La sorgente sta tra i due NaI


| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -10 mV  |
|     3    |   20 mV   | NegEdge   |    -7 mV   | 
|     4    |   20 mV   | NegEdge   |    -7 mV   |

Trigger Pattern : (no.2 ) & (no. 3) & (no. 4)


---------------------------------------------------------

- FILE NAME : Na2_2.dst

Calibrazione dei PMT
NaI1 (ch.3) deve vedere il 1200 keV mentre NaI2 e LYSO devono vedere i due fotoni a 511 keV

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -4 mV   |
|     3    |   50 mV   | NegEdge   |    -10 mV  |
|     4    |   20 mV   | NegEdge   |    -7 mV   |

Trigger Pattern : (no.2 ) & (no. 3) & (no. 4)

--------------------------------------------------------

 - FILE NAME : LYSO5

Background LYSO senza sorgenti 

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -1 mV   |
|     3    |   10 mV   | NegEdge   |    -5 mV   | (Veto)
|     4    |   10 mV   | NegEdge   |    -5 mV   | (Veto)

Trigger Pattern : (no.2 ) & (~no. 3) & (~no. 4)

------------------------------------------------

-- FILE NAME : CS2

Misura dello spettro gamma del Cs 137. Misura da fare dopo la calibrazione.

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -1 mV   |
|     3    |   10 mV   | NegEdge   |    -5 mV   | (Veto)
|     4    |   10 mV   | NegEdge   |    -5 mV   | (Veto)

Trigger Pattern : (no.2 ) & (~no. 3) & (~no. 4)

---------------------------------------------------------------

- FILE NAME : LYSO6

Misura di fondo

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -1 mV   |
|     3    |   10 mV   | NegEdge   |    -5 mV   |
|     4    |   10 mV   | NegEdge   |    -5 mV   |

Trigger Pattern : (no.2 ) & (~no. 3) & (~no. 4)

