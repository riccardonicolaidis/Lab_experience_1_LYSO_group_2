# Lab esperienza 1

- FILE NAME: LYSO3.dst ID 300
- FILE NAME: LYSO4.dst ID 400

Measurement of 200 keV or 300 keV and beta decay in the LYSO

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

Calibration of the NaI scintillators with Co 60 source

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   2 mV    | NegEdge   |   -2 mV    | (Veto)
|     3    |   50 mV   | NegEdge   |    -5 mV   |
|     4    |   50 mV   | NegEdge   |    -5 mV   |

Trigger Pattern (~no.2 ) & (no. 3) & (no. 4)


-------------------------------------------------------

- FILE NAME: Co2_2.dst ID 500

Calibratione of the LYSO crystal with C0 60 source

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -15 mV  |
|     3    |   10 mV   | No        |    -5 mV   | (Veto)
|     4    |   50 mV   | NegEdge   |    -33 mV  |

Trigger	Pattern	(no.2 ) & (~no. 3) & (no. 4)


-----------------------------------------------

- FILE NAME: Na2_1.dst

Calibration with Na22 source
LYSO should see 1200 keV
The source is between the two NaIs


| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -10 mV  |
|     3    |   20 mV   | NegEdge   |    -7 mV   | 
|     4    |   20 mV   | NegEdge   |    -7 mV   |

Trigger Pattern : (no.2 ) & (no. 3) & (no. 4)


---------------------------------------------------------

- FILE NAME : Na2_2.dst

PMTs calibration
NaI1 (ch.3) should see the 1200 keV peak while NaI2 and LYSO should se the two photons at 511 keV

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -4 mV   |
|     3    |   50 mV   | NegEdge   |    -10 mV  |
|     4    |   20 mV   | NegEdge   |    -7 mV   |

Trigger Pattern : (no.2 ) & (no. 3) & (no. 4)

--------------------------------------------------------

 - FILE NAME : LYSO5

Background LYSO without sources 

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -1 mV   |
|     3    |   10 mV   | NegEdge   |    -5 mV   | (Veto)
|     4    |   10 mV   | NegEdge   |    -5 mV   | (Veto)

Trigger Pattern : (no.2 ) & (~no. 3) & (~no. 4)

------------------------------------------------

-- FILE NAME : CS2

Measurement of the gamma spectrum of Cs 137. Measurement to do after the calibration.

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -1 mV   |
|     3    |   10 mV   | NegEdge   |    -5 mV   | (Veto)
|     4    |   10 mV   | NegEdge   |    -5 mV   | (Veto)

Trigger Pattern : (no.2 ) & (~no. 3) & (~no. 4)

---------------------------------------------------------------

- FILE NAME : LYSO6

Background measurement

| Channel  |  Y scale  | Trigger   |  Threshold |
|----------|-----------|-----------|------------|
|     1    |   2 mV    | No        |            |
|     2    |   10 mV   | NegEdge   |    -1 mV   |
|     3    |   10 mV   | NegEdge   |    -5 mV   |
|     4    |   10 mV   | NegEdge   |    -5 mV   |

Trigger Pattern : (no.2 ) & (~no. 3) & (~no. 4)

