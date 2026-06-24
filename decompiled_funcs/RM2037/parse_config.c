
void parse_config(void)

{
  bool bVar1;
  byte bVar2;
  byte *pbVar3;
  char *pcVar4;
  byte *pbVar5;
  byte *pbVar6;
  undefined4 extraout_r1;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  uint uVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined4 *puVar13;
  uint uVar14;
  uint uVar15;
  bool bVar16;
  uint uVar17;
  uint uVar18;
  byte abStack_2338 [16];
  byte abStack_2328 [8176];
  byte local_338;
  char local_337;
  undefined1 local_336;
  undefined1 local_335;
  byte abStack_333 [507];
  undefined4 local_138;
  undefined *local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined2 local_2c;
  uint local_28;
  
  g_bright_clock_ctrl = 0x5a0;
  DAT_20031904 = 4;
  iVar8 = 0;
  g_dwCfgIgnoreDp = 0;
  DAT_2003185c = 1;
  g_dwCfgDdxFixedSet = 0;
  DAT_20072280 = 0;
  g_dwCfgStartTimedOut = 0;
  g_dwCfgDdxFixedAux = 0;
  g_bCfgDefSeqEffect = 0x49;
  g_dwCfgDoublesided = 0;
  g_dwCfgSwapCharCount = 0;
  do {
    *(undefined4 *)((int)&g_dwCfgDlmxLinesPerIndex + iVar8) = 0;
    iVar8 = iVar8 + 4;
  } while (iVar8 != 0x40);
  iVar8 = 0;
  do {
    puVar11 = &g_dwCfgDlmxX + iVar8 * 0xf0;
    iVar7 = 0;
    do {
      *puVar11 = 0;
      puVar11[1] = 0;
      puVar11[2] = 0;
      puVar11[3] = 0;
      iVar7 = iVar7 + 1;
      puVar11 = puVar11 + 4;
    } while (iVar7 != 0x3c);
    iVar8 = iVar8 + 1;
  } while (iVar8 != 0x10);
  iVar8 = 0;
  do {
    *(undefined4 *)((int)&g_dwCfgMissingLeds + iVar8) = 0;
    iVar8 = iVar8 + 4;
  } while (iVar8 != 0x20);
  g_dwCfgHygrosenTempProbe = 0;
  DAT_2008c180 = 0x2b;
  DAT_20090a60 = 0x2b;
  DAT_2008c181 = 0x30;
  DAT_20090a61 = 0x30;
  DAT_2008c182 = 0x30;
  DAT_20090a62 = 0x30;
  DAT_2008c183 = 0x30;
  DAT_20090a63 = 0x30;
  DAT_2008c184 = 0x5f;
  DAT_20090a64 = 0x5f;
  DAT_20090a65 = 0x43;
  DAT_2008c185 = 0;
  DAT_20090a66 = 0;
  g_dwCfgDlmxCount = 0;
  g_dwCfgSuppressHourLz = 0;
  g_dwCfgSuppressMinsLz = 0;
  g_dwCfgSuppressSecsLz = 0;
  g_dwCfgSuppressDayLz = 0;
  g_dwCfgReplaceHoursLz = 1;
  g_dwCfgSuppressMonLz = 0;
  g_dwCfgScrollIfTooWide = 1;
  g_dwCfgTruncateOnChar = 0;
  g_dwCfgTruncateOnWord = 0;
  g_dwCfgEdfAlwaysDefault = 0;
  puVar11 = &DAT_20090a68;
  iVar8 = 0;
  do {
    puVar11[2] = 0;
    puVar11[1] = 0;
    puVar11[4] = 0xffffffff;
    puVar11[5] = 0xffffffff;
    puVar11[6] = 0xffffffff;
    puVar11[7] = 0xffffffff;
    puVar11[8] = 0xffffffff;
    *(undefined1 *)((int)puVar11 + 0x49) = 0x20;
    *(undefined1 *)(puVar11 + 0xe) = 0x20;
    *(undefined1 *)((int)puVar11 + 0x4b) = 0;
    FUN_200024f0(&DAT_20090ad8 + iVar8 * 0x170,0,0x100);
    iVar8 = iVar8 + 1;
    puVar11 = puVar11 + 0x5c;
  } while (iVar8 != 0x100);
  puVar13 = &DAT_200a7a68;
  iVar8 = 0;
  puVar11 = puVar13;
  do {
    *puVar13 = 0xffffffff;
    *(undefined1 *)(puVar13 + 1) = 0x20;
    puVar11[0x44] = 0xffffffff;
    FUN_200024f0(&DAT_200a7a6e + iVar8 * 0x1d8,0,0x32);
    iVar8 = iVar8 + 1;
    puVar13 = puVar13 + 0x76;
    puVar11 = puVar11 + 0x77;
  } while (iVar8 != 0x100);
  DAT_20072414 = 0;
  DAT_2007224c = 0;
  DAT_20072250 = 0;
  iVar8 = 0;
  do {
    *(undefined4 *)((int)&g_dwCfgLinesPerChannel + iVar8) = 0;
    *(undefined4 *)((int)&DAT_2008c188 + iVar8) = 0;
    *(undefined4 *)((int)&g_dwCfgChannelLengths + iVar8) = 1;
    iVar8 = iVar8 + 4;
  } while (iVar8 != 0x20);
  DAT_20072218 = 0;
  iVar8 = 0;
  do {
    (&DAT_2008c1ac)[iVar8] = 0;
    iVar8 = iVar8 + 1;
  } while (iVar8 != 0x4800);
  g_dwCfgFlashSpeedA = 0x3c;
  g_dwCfgFlashSpeedB = 0x28;
  g_dwCfgTimeout = 0;
  DAT_200722a0 = 0;
  g_dwCfgSequenceMs = 2000;
  g_dwCfgPixels = 0x100;
  g_dwCfgFxSlowdown = 0;
  g_dwCfgChannels = 8;
  g_dwCfgColours = 2;
  g_dwCfgRowsPerLine = 8;
  g_abCfgPsu = 'N';
  g_dwCfgTempEnabled = 1;
  DAT_2007227c = 0;
  puVar11 = &DAT_20545718;
  DAT_20545718 = 0;
  do {
    puVar11 = puVar11 + 1;
    *puVar11 = 0xffffffff;
  } while (puVar11 != (undefined4 *)0x20545740);
  DAT_200909ac = 0;
  g_dwCfgEdfCntDown = 0;
  g_dwArabicLigatureCount = 0;
  g_protocol_5 = 0;
  g_protocol_1 = 0;
  g_protocol_4 = 0;
  g_protocol_2 = 0;
  g_protocol_3 = 0;
  g_protocol_7 = 0;
  iVar8 = SPI0_transfer_file(0,abStack_2338,0x47464341);
  if (iVar8 != 0) {
    pbVar6 = abStack_2328;
    uVar15 = 0;
    bVar1 = false;
    uVar10 = uVar15;
switchD_20008af4_caseD_4a:
    do {
      pbVar6 = (byte *)FUN_20004574((char *)pbVar6,(char *)&local_338,0x200);
      if ((pbVar6 == (byte *)0x0) || ((local_338 == 0x2e && (local_337 == '\0'))))
      goto LAB_2000b4d4;
      pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"DDXmodalPage=");
      if (pbVar3 != (byte *)0x0) {
        pbVar3 = atoi(pbVar3,(int *)&local_28);
        g_dwCfgDdxModalV1 = local_28;
        pbVar3 = atoi(pbVar3 + 1,(int *)&local_28);
        g_dwCfgDdxModalV2 = local_28;
        pbVar3 = atoi(pbVar3 + 1,(int *)&local_28);
        g_dwCfgDdxModalV3 = local_28;
        atoi(pbVar3 + 1,(int *)&local_28);
        g_dwCfgDdxModalV4 = local_28;
        bVar1 = true;
        goto switchD_20008af4_caseD_4a;
      }
      pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"DDXfixedPage=");
      if (pbVar3 != (byte *)0x0) {
        pbVar3 = atoi(pbVar3,(int *)&g_dwCfgDdxFixedPage);
        if ((pbVar3[1] & 0x5f) == 0x4e) {
          g_dwCfgDdxFixedYn = 0;
        }
        else if ((pbVar3[1] & 0x5f) == 0x59) {
          g_dwCfgDdxFixedYn = 1;
        }
        pbVar3 = pbVar3 + 3;
        g_dwCfgDdxFixedSet = 1;
        iVar8 = 1;
        while ((*pbVar3 != 0x40 && (iVar8 < 0x14))) {
          if (*pbVar3 == 0x78) {
            pbVar3 = atoi(pbVar3 + 1,(int *)&local_28);
            uVar17 = local_28;
            pbVar3 = atoi(pbVar3 + 1,(int *)&local_28);
            uVar14 = local_28;
            pbVar3 = atoi(pbVar3 + 1,(int *)&local_28);
            uVar18 = local_28;
            pbVar5 = atoi(pbVar3 + 1,(int *)&local_28);
            iVar12 = iVar8 + -1;
            (&g_dwCfgDdxZoneX)[iVar12 * 4] = uVar17;
            (&g_dwCfgDdxZoneY)[iVar12 * 4] = uVar14;
            (&g_dwCfgDdxZoneH)[iVar12 * 4] = local_28;
            (&g_dwCfgDdxZoneW)[iVar12 * 4] = uVar18;
            iVar7 = 0;
            bVar16 = false;
            pbVar3 = &g_abCfgDdxZoneNames + iVar12 * 0x100;
            while ((pbVar5[iVar7 + 1] != 0x3e && (iVar7 != 0x100))) {
              pbVar9 = pbVar3 + 1;
              *pbVar3 = pbVar5[iVar7 + 1];
              iVar7 = iVar7 + 1;
              pbVar3 = pbVar9;
              if (0xff < iVar7) {
                bVar16 = true;
              }
            }
            if (!bVar16) {
              (&g_abCfgDdxZoneNames)[iVar12 * 0x100 + iVar7] = 0x3e;
              (&g_abCfgDdxZoneNames)[iVar12 * 0x100] = 0;
              iVar8 = iVar8 + 1;
            }
            iVar12 = iVar8 + -1;
            (&g_dwCfgDdxZoneX)[iVar12 * 4] = 0xffffffff;
            (&g_dwCfgDdxZoneY)[iVar12 * 4] = 0xffffffff;
            (&g_dwCfgDdxZoneH)[iVar12 * 4] = 0xffffffff;
            (&g_dwCfgDdxZoneW)[iVar12 * 4] = 0xffffffff;
            (&g_abCfgDdxZoneNames)[iVar12 * 0x100] = 0;
            if (pbVar5[iVar7 + 1] == 0x40) break;
            pbVar6 = (byte *)FUN_20004574((char *)pbVar6,(char *)&local_338,0x200);
          }
          else {
            pbVar6 = (byte *)FUN_20004574((char *)pbVar6,(char *)&local_338,0x200);
          }
          pbVar3 = &local_338;
        }
      }
      pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"DDXfixedLine=");
      if (pbVar3 == (byte *)0x0) {
        pcVar4 = strcmp_w_equals((char *)&local_338,"DLMx=");
        if (pcVar4 != (char *)0x0) {
          g_dwCfgTotalWidthDlmx = 0;
          if (g_dwCfgChannels != 0) {
            uVar17 = 0;
            do {
              g_dwCfgTotalWidthDlmx = (&g_dwCfgChannelLengths)[uVar17] + g_dwCfgTotalWidthDlmx;
              uVar17 = uVar17 + g_dwCfgColours;
            } while (uVar17 < g_dwCfgChannels);
          }
          atoi((byte *)(pcVar4 + 1),(int *)&local_28);
          uVar17 = local_28;
          g_dwCfgDlmxCount = g_dwCfgDlmxCount + 1;
          pbVar3 = pbVar6;
          if (local_28 == 0) {
            g_dwCfgDlmxHasZero = 1;
          }
          while (*pbVar3 != 0x2a) {
            pbVar5 = pbVar3 + 1;
            bVar2 = *pbVar3;
            pbVar3 = pbVar5;
            if (true) {
              switch(bVar2) {
              case 0x68:
                pbVar3 = atoi(pbVar5,(int *)&local_28);
                (&g_dwCfgDlmxH)[(uVar17 * 0x3c + uVar15) * 4] = local_28;
                break;
              case 0x6c:
                pbVar3 = atoi(pbVar5,(int *)&local_28);
                uVar15 = local_28 - 1;
                break;
              case 0x77:
                pbVar3 = atoi(pbVar5,(int *)&local_28);
                (&g_dwCfgDlmxW)[(uVar17 * 0x3c + uVar15) * 4] = local_28;
                break;
              case 0x78:
                pbVar3 = atoi(pbVar5,(int *)&local_28);
                (&g_dwCfgDlmxX)[(uVar17 * 0x3c + uVar15) * 4] = local_28;
                break;
              case 0x79:
                pbVar3 = atoi(pbVar5,(int *)&local_28);
                (&g_dwCfgDlmxY)[(uVar17 * 0x3c + uVar15) * 4] = local_28;
              }
            }
          }
          uVar14 = uVar15 + 1;
          uVar15 = uVar14;
          if (g_dwCfgDoublesided != 0) {
            uVar15 = uVar14 * 2;
            uVar14 = uVar14 & 0x7fffffff;
            if (uVar14 != 0) {
              uVar18 = 0;
              iVar8 = uVar17 * 0x3c;
              do {
                iVar7 = 0;
                puVar11 = &g_dwCfgDlmxX + (iVar8 + uVar18 + uVar14) * 4;
                puVar13 = &g_dwCfgDlmxX + (iVar8 + uVar18) * 4;
                do {
                  *puVar11 = *puVar13;
                  iVar7 = iVar7 + 1;
                  puVar11 = puVar11 + 1;
                  puVar13 = puVar13 + 1;
                } while (iVar7 != 4);
                iVar7 = iVar8 + uVar18 + uVar14;
                (&g_dwCfgDlmxY)[iVar7 * 4] =
                     g_dwCfgRowsPerLine * (g_dwCfgTotalWidthDlmx >> 1) + (&g_dwCfgDlmxY)[iVar7 * 4];
                uVar18 = uVar18 + 1;
              } while (uVar18 != uVar14);
            }
          }
          (&g_dwCfgDlmxLinesPerIndex)[uVar17] = uVar15;
          goto switchD_20008af4_caseD_4a;
        }
        pcVar4 = strcmp_w_equals((char *)&local_338,"CurrentMode=");
        if (pcVar4 != (char *)0x0) {
          if (true) {
            switch(pcVar4[1]) {
            case '0':
              g_dwCfgCurrentMode = 0;
              goto switchD_20008af4_caseD_4a;
            case '1':
              g_dwCfgCurrentMode = 1;
              goto switchD_20008af4_caseD_4a;
            case '2':
              g_dwCfgCurrentMode = 2;
              goto switchD_20008af4_caseD_4a;
            case '3':
              g_dwCfgCurrentMode = 3;
              goto switchD_20008af4_caseD_4a;
            case '4':
              g_dwCfgCurrentMode = 4;
              goto switchD_20008af4_caseD_4a;
            case '5':
              g_dwCfgCurrentMode = 5;
              goto switchD_20008af4_caseD_4a;
            case '6':
              g_dwCfgCurrentMode = 6;
              goto switchD_20008af4_caseD_4a;
            case '7':
              g_dwCfgCurrentMode = 7;
              goto switchD_20008af4_caseD_4a;
            case '8':
              g_dwCfgCurrentMode = 8;
              goto switchD_20008af4_caseD_4a;
            case '9':
              g_dwCfgCurrentMode = 9;
              goto switchD_20008af4_caseD_4a;
            case 'A':
              g_dwCfgCurrentMode = 10;
              goto switchD_20008af4_caseD_4a;
            case 'B':
              g_dwCfgCurrentMode = 0xb;
              goto switchD_20008af4_caseD_4a;
            case 'C':
              g_dwCfgCurrentMode = 0xc;
              goto switchD_20008af4_caseD_4a;
            case 'D':
              g_dwCfgCurrentMode = 0xd;
              goto switchD_20008af4_caseD_4a;
            case 'E':
              g_dwCfgCurrentMode = 0xe;
              goto switchD_20008af4_caseD_4a;
            case 'F':
              g_dwCfgCurrentMode = 0xf;
              goto switchD_20008af4_caseD_4a;
            }
          }
          g_dwCfgCurrentMode = 1;
          goto switchD_20008af4_caseD_4a;
        }
        pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"autoDetectArabic=");
        if (pbVar3 == (byte *)0x0) {
          pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"translateArabic=");
          if (pbVar3 == (byte *)0x0) {
            pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"RepeatDLs=");
            if (pbVar3 == (byte *)0x0) {
              pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"ClearOldQueue=");
              if (pbVar3 == (byte *)0x0) {
                pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"queueMsThenSs=");
                if (pbVar3 == (byte *)0x0) {
                  pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"carryLastlines=");
                  if (pbVar3 == (byte *)0x0) {
                    pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"CarryPageContent=");
                    if (pbVar3 == (byte *)0x0) {
                      pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"Succession=");
                      if (pbVar3 == (byte *)0x0) {
                        pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"EDFcntDownEaAnsEd=");
                        if (pbVar3 == (byte *)0x0) {
                          pcVar4 = strcmp_w_equals((char *)&local_338,"MainChannel=");
                          if (pcVar4 == (char *)0x0) {
                            pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"defSeqEffect=");
                            if (pbVar3 == (byte *)0x0) {
                              pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,
                                                               "HygrosenTempProbe=");
                              if (pbVar3 == (byte *)0x0) {
                                pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,"defMsgJust=");
                                if (pbVar3 == (byte *)0x0) {
                                  pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,
                                                                   "defMsgEffect=");
                                  if (pbVar3 == (byte *)0x0) {
                                    pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,
                                                                     "defMsgDuration=");
                                    if (pbVar3 != (byte *)0x0) {
                                      atoi(pbVar3,(int *)&local_28);
                                      g_dwCfgDefMsgDuration = local_28;
                                    }
                                    pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,
                                                                     "scrollIfTooWide=");
                                    if (pbVar3 == (byte *)0x0) {
                                      pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,
                                                                       "truncateOnChar=");
                                      if (pbVar3 == (byte *)0x0) {
                                        pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,
                                                                         "truncateOnWord=");
                                        if (pbVar3 == (byte *)0x0) {
                                          pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,

                                                  "suppressHourLeadingZero=");
                                          if (pbVar3 == (byte *)0x0) {
                                            pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,

                                                  "suppressMinsLeadingZero=");
                                            if (pbVar3 == (byte *)0x0) {
                                              pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,

                                                  "suppressSecsLeadingZero=");
                                              if (pbVar3 == (byte *)0x0) {
                                                pbVar3 = (byte *)strcmp_w_equals((char *)&local_338,

                                                  "suppressDayLeadingZero=");
                                                if (pbVar3 == (byte *)0x0) {
                                                  pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"replaceHoursLeadingZero=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"suppressMonLeadingZero=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"EDFalwaysDefault=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"EDFmaximumTrains=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"ArabicLigatures=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pcVar4 = strcmp_w_equals((char *)&local_338,
                                                                             "EDF_PAGE=");
                                                    if (pcVar4 == (char *)0x0) {
                                                      pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"ChannelLengths=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"missingLEDs=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"LinesPerChannel=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pcVar4 = strcmp_w_equals((char *)&local_338,
                                                                             "PSU=");
                                                    if (pcVar4 == (char *)0x0) {
                                                      pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"doublesided=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"swapChar=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"ignoreDP=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"LightSensor=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"Temp=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"LEDmon=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"DriveType=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"speedDivisorM=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"speedDivisorD=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"BrightControl=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"Pixels=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"Channels=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"Colours=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"RowsPerLine=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"Speed=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"FXslowdown=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"PROTOCOL=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"RGSwap=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"RBSwap=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"Master=");
                                                  if (pbVar3 != (byte *)0x0) {
                                                    g_dwCfgMaster = (uint)((*pbVar3 & 0x5f) == 0x59)
                                                    ;
                                                    goto switchD_20008af4_caseD_4a;
                                                  }
                                                  pcVar4 = strcmp_w_equals((char *)&local_338,
                                                                           "StartTimedOut=");
                                                  if ((pcVar4 != (char *)0x0) && (*pcVar4 == 'Y')) {
                                                    g_dwCfgStartTimedOut = 1;
                                                    g_dwCfgStartTimedOutInit = 1;
                                                    if ((pcVar4[1] == '\0') || (pcVar4[1] == ' '))
                                                    goto switchD_20008af4_caseD_4a;
                                                  }
                                                  pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"Timeout=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"Sequence=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"Flash=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"MaintTime=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"PinLock=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"MaxADC=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"MinBr=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"MaxBr=");
                                                  if (pbVar3 == (byte *)0x0) {
                                                    pbVar3 = (byte *)strcmp_w_equals((char *)&
                                                  local_338,"DST=");
                                                  if (pbVar3 != (byte *)0x0) {
                                                    pbVar3 = atoi(pbVar3,(int *)&local_28);
                                                    g_dwCfgDstStartMonth = local_28;
                                                    if ((*pbVar3 == 0x2c) &&
                                                       (g_dwCfgDstStartWeek = (uint)pbVar3[1],
                                                       pbVar3[2] == 0x2c)) {
                                                      pbVar3 = atoi(pbVar3 + 3,(int *)&local_28);
                                                      g_dwCfgDstEndMonth = local_28;
                                                      if (*pbVar3 == 0x2c) {
                                                        g_dwCfgDstEndWeek = (uint)pbVar3[1];
                                                        g_dwCfgDstStartDow = 2;
                                                        g_dwCfgDstEndDow = 1;
                                                        if (pbVar3[2] == 0x2c) {
                                                          pbVar3 = atoi(pbVar3 + 3,(int *)&local_28)
                                                          ;
                                                          g_dwCfgDstStartDow = local_28;
                                                          if (*pbVar3 != 0x2c)
                                                          goto switchD_20008af4_caseD_4a;
                                                          atoi(pbVar3 + 1,(int *)&local_28);
                                                          g_dwCfgDstEndDow = local_28;
                                                        }
                                                        g_dst_valid_marker = 0;
                                                        if ((((g_dwCfgDstStartMonth - 1 < 0xc) &&
                                                             (g_dwCfgDstEndMonth - 1 < 0xc)) &&
                                                            (g_dwCfgDstStartMonth <
                                                             g_dwCfgDstEndMonth)) && (true)) {
                                                          switch(g_dwCfgDstStartWeek) {
                                                          case 0x46:
                                                            g_dwCfgDstStartWeek = 1;
                                                            break;
                                                          default:
                                                            goto switchD_20008af4_caseD_4a;
                                                          case 0x4c:
                                                            g_dwCfgDstStartWeek = 5;
                                                            break;
                                                          case 0x51:
                                                            g_dwCfgDstStartWeek = 4;
                                                            break;
                                                          case 0x53:
                                                            g_dwCfgDstStartWeek = 2;
                                                            break;
                                                          case 0x54:
                                                            g_dwCfgDstStartWeek = 3;
                                                          }
                                                          if (true) {
                                                            switch(g_dwCfgDstEndWeek) {
                                                            case 0x46:
                                                              g_dwCfgDstEndWeek = 1;
                                                              break;
                                                            default:
                                                              goto switchD_20008af4_caseD_4a;
                                                            case 0x4c:
                                                              g_dwCfgDstEndWeek = 5;
                                                              break;
                                                            case 0x51:
                                                              g_dwCfgDstEndWeek = 4;
                                                              break;
                                                            case 0x53:
                                                              g_dwCfgDstEndWeek = 2;
                                                              break;
                                                            case 0x54:
                                                              g_dwCfgDstEndWeek = 3;
                                                            }
                                                            g_dst_valid_marker = 0x31121955;
                                                            FUN_200072ac();
                                                            FUN_20006874();
                                                          }
                                                        }
                                                      }
                                                    }
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 < 0x19) {
                                                      local_28 = 0x1e;
                                                    }
                                                    else if (0x62 < local_28) {
                                                      local_28 = 0x62;
                                                    }
                                                    g_dwCfgMaxBrightness = local_28;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 == 0) {
                                                      local_28 = 1;
                                                    }
                                                    else if (0x14 < local_28) {
                                                      local_28 = 0x14;
                                                    }
                                                    g_dwCfgMinBrightness = local_28;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 < 5) {
                                                      local_28 = 5;
                                                    }
                                                    else if (0x7f < local_28) {
                                                      local_28 = 0x7f;
                                                    }
                                                    g_dwCfgMaxAdc = local_28;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 == 0) {
                                                      local_28 = 1;
                                                    }
                                                    else if (0x3c < local_28) {
                                                      local_28 = 0x3c;
                                                    }
                                                    g_dwCfgPinLock = local_28;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 == 0) {
                                                      local_28 = 1;
                                                    }
                                                    else if (0xf < local_28) {
                                                      local_28 = 0xf;
                                                    }
                                                    g_dwCfgMaintTime = local_28;
                                                  }
                                                  }
                                                  else {
                                                    pbVar3 = atoi(pbVar3,(int *)&local_28);
                                                    if (999 < local_28) {
                                                      local_28 = 1000;
                                                    }
                                                    g_dwCfgFlashSpeedA = local_28 / 10;
                                                    g_dwCfgFlashSpeedB = g_dwCfgFlashSpeedA;
                                                    if (*pbVar3 == 0x2c) {
                                                      atoi(pbVar3 + 1,(int *)&local_28);
                                                      if (999 < local_28) {
                                                        local_28 = 1000;
                                                      }
                                                      g_dwCfgFlashSpeedB = local_28 / 10;
                                                    }
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 == 0) {
                                                      local_28 = 1;
                                                    }
                                                    else if (0x5a < local_28) {
                                                      local_28 = 0x5a;
                                                    }
                                                    g_dwCfgSequenceMs = local_28 * 1000;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (99 < local_28) {
                                                      local_28 = 99;
                                                    }
                                                    g_dwCfgTimeout = local_28;
                                                  }
                                                  goto switchD_20008af4_caseD_4a;
                                                  }
                                                  if ((*pbVar3 & 0x5f) == 0x4e) {
                                                    g_dwCfgRgbSwapBits =
                                                         g_dwCfgRgbSwapBits & 0xfffffffd;
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x59) {
                                                    g_dwCfgRgbSwapBits = g_dwCfgRgbSwapBits | 2;
                                                  }
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x4e) {
                                                    g_dwCfgRgbSwapBits =
                                                         g_dwCfgRgbSwapBits & 0xfffffffe;
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x59) {
                                                    g_dwCfgRgbSwapBits = g_dwCfgRgbSwapBits | 1;
                                                  }
                                                  }
                                                  else {
                    /* PROTOCOL= */
                                                    atoi(pbVar3,(int *)&local_28);
                                                    switch(local_28) {
                                                    case 1:
                                                      g_protocol_1 = 1;
                                                      break;
                                                    case 2:
                                                      g_protocol_2 = 1;
                                                      break;
                                                    case 3:
                                                      g_protocol_3 = 1;
                                                      g_protocol_1 = 1;
                                                      break;
                                                    case 4:
                                                      g_protocol_4 = 1;
                                                      break;
                                                    case 5:
                                                      g_protocol_5 = 1;
                                                      break;
                                                    case 6:
                                                      g_protocol_6 = 1;
                                                      break;
                                                    case 7:
                                                      g_protocol_2 = 1;
                                                      g_protocol_7 = 1;
                                                    }
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (9 < local_28) {
                                                      local_28 = 9;
                                                    }
                                                    g_dwCfgFxSlowdown = local_28;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 < 0x32) {
                                                      local_28 = 0x32;
                                                    }
                                                    else if (600 < local_28) {
                                                      local_28 = 600;
                                                    }
                                                    g_bright_clock_ctrl =
                                                         division(0x8ca00,local_28 *
                                                                          g_dwCfgRowsPerLine);
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 < 7) {
                                                      local_28 = 7;
                                                    }
                                                    else if (9 < local_28) {
                                                      local_28 = 9;
                                                    }
                                                    g_dwCfgRowsPerLine = local_28;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 == 0) {
                                                      local_28 = 1;
                                                    }
                                                    else if (3 < local_28) {
                                                      local_28 = 3;
                                                    }
                                                    g_dwCfgColours = local_28;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 == 0) {
                                                      local_28 = 1;
                                                    }
                                                    else if (8 < local_28) {
                                                      local_28 = 8;
                                                    }
                                                    g_dwCfgChannels = local_28;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    g_dwCfgPixels = local_28 + 7 & 0xfffffff8;
                                                  }
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x44) {
                                                    g_dwCfgBrightControl = 0x44;
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x4f) {
                                                    g_dwCfgBrightControl = 0x4f;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 == 0) {
                                                      local_28 = 1;
                                                    }
                                                    else if (0x13 < local_28) {
                                                      local_28 = 0x13;
                                                    }
                                                    g_dwCfgSpeedDivisorD = local_28;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    if (local_28 == 0) {
                                                      local_28 = 1;
                                                    }
                                                    else if (0x13 < local_28) {
                                                      local_28 = 0x13;
                                                    }
                                                    g_dwCfgSpeedDivisorM = local_28;
                                                  }
                                                  }
                                                  else {
                                                    bVar2 = *pbVar3 & 0x5f;
                                                    if (bVar2 == 0x4d) {
                                                      g_drive_type._0_1_ = 'M';
                                                    }
                                                    else if (bVar2 == 0x54) {
                                                      g_drive_type._0_1_ = 'T';
                                                    }
                                                    else if (bVar2 == 0x44) {
                                                      g_drive_type._0_1_ = 'D';
                                                    }
                                                  }
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x4e) {
                                                    g_dwCfgLedmonEnabled = 0;
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x59) {
                                                    g_dwCfgLedmonEnabled = 1;
                                                  }
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x4e) {
                                                    g_dwCfgTempEnabled = 0;
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x59) {
                                                    g_dwCfgTempEnabled = 1;
                                                  }
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x4e) {
                                                    g_dwCfgLightSensorEnabled = 0;
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x59) {
                                                    g_dwCfgLightSensorEnabled = 1;
                                                  }
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x4e) {
                                                    g_dwCfgIgnoreDp = 0;
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x59) {
                                                    g_dwCfgIgnoreDp = 1;
                                                  }
                                                  }
                                                  else {
                                                    iVar8 = FUN_200044b8(pbVar3,(int *)&local_28);
                                                    (&g_abCfgSwapCharTable)
                                                    [g_dwCfgSwapCharCount * 2] = (char)local_28;
                                                    FUN_200044b8((byte *)(iVar8 + 1),
                                                                 (int *)&local_28);
                                                    (&DAT_2008a9dd)[g_dwCfgSwapCharCount * 2] =
                                                         (char)local_28;
                                                    g_dwCfgSwapCharCount = g_dwCfgSwapCharCount + 1;
                                                  }
                                                  }
                                                  else {
                                                    g_dwCfgDoublesided =
                                                         (uint)((*pbVar3 & 0x5f) == 0x59);
                                                  }
                                                  }
                                                  else {
                                                    g_abCfgPsu = *pcVar4;
                                                  }
                                                  }
                                                  else {
                                                    iVar8 = 0;
                                                    do {
                                                      *(undefined4 *)
                                                       ((int)&g_dwCfgChannelLengths + iVar8) = 1;
                                                      iVar8 = iVar8 + 4;
                                                    } while (iVar8 != 0x20);
                                                    iVar8 = 0;
                                                    do {
                                                      pbVar5 = atoi(pbVar3,(int *)&local_28);
                                                      *(uint *)((int)&g_dwCfgChannelLengths + iVar8)
                                                           = local_28;
                                                      pbVar3 = pbVar5 + 1;
                                                      if (*pbVar5 != 0x2c) break;
                                                      iVar8 = iVar8 + 4;
                                                    } while (iVar8 != 0x20);
                                                  }
                                                  }
                                                  else {
                                                    iVar8 = 0;
                                                    do {
                                                      pbVar5 = atoi(pbVar3,(int *)&local_28);
                                                      *(uint *)((int)&g_dwCfgMissingLeds + iVar8) =
                                                           local_28;
                                                      pbVar3 = pbVar5 + 1;
                                                      if (*pbVar5 != 0x2c) break;
                                                      iVar8 = iVar8 + 4;
                                                    } while (iVar8 != 0x20);
                                                  }
                                                  }
                                                  else {
                                                    iVar8 = 0;
                                                    do {
                                                      *(undefined4 *)
                                                       ((int)&g_dwCfgLinesPerChannel + iVar8) = 0;
                                                      iVar8 = iVar8 + 4;
                                                    } while (iVar8 != 0x20);
                                                    iVar8 = 0;
                                                    do {
                                                      pbVar5 = atoi(pbVar3,(int *)&local_28);
                                                      *(uint *)((int)&g_dwCfgLinesPerChannel + iVar8
                                                               ) = local_28;
                                                      pbVar3 = pbVar5 + 1;
                                                      if (*pbVar5 != 0x2c) break;
                                                      iVar8 = iVar8 + 4;
                                                    } while (iVar8 != 0x20);
                                                    uVar10 = 1;
                                                  }
                                                  }
                                                  else {
                                                    local_38 = (undefined *)0x78737021;
                                                    local_34 = 0x64217878;
                                                    local_30 = 0x78787870;
                                                    local_2c = 0x6d21;
                                                    DAT_2008a8a8 = 0;
                                                    iVar8 = DAT_200a7a68;
                                                    if (true) {
                                                      while ((iVar8 != -1 &&
                                                             (DAT_2008a8a8 = DAT_2008a8a8 + 1,
                                                             DAT_2008a8a8 < 0x100))) {
                                                        iVar8 = (&DAT_200a7a68)[DAT_2008a8a8 * 0x76]
                                                        ;
                                                      }
                                                    }
                                                    if ((&DAT_200a7a68)[DAT_2008a8a8 * 0x76] == -1)
                                                    {
                                                      (&DAT_200a7a6c)[DAT_2008a8a8 * 0x1d8] =
                                                           *pcVar4;
                                                      (&DAT_200a7a6d)[DAT_2008a8a8 * 0x1d8] =
                                                           pcVar4[2];
                                                      iVar8 = 0;
                                                      do {
                                                        (&DAT_200a7a6e)
                                                        [DAT_2008a8a8 * 0x1d8 + iVar8] =
                                                             *(undefined1 *)((int)&local_38 + iVar8)
                                                        ;
                                                        iVar8 = iVar8 + 1;
                                                      } while (iVar8 != 0xf);
                                                      (&DAT_200a7a7c)[DAT_2008a8a8 * 0x1d8] =
                                                           (&DAT_200a7a6d)[DAT_2008a8a8 * 0x1d8];
                                                      (&DAT_200a7a77)[DAT_2008a8a8 * 0x1d8] =
                                                           pcVar4[4];
                                                      (&DAT_200a7a78)[DAT_2008a8a8 * 0x1d8] =
                                                           pcVar4[5];
                                                      (&DAT_200a7a79)[DAT_2008a8a8 * 0x1d8] =
                                                           pcVar4[6];
                                                      iVar8 = DAT_2008a8a8;
                                                      iVar7 = parse_digits(&DAT_200a7a77 +
                                                                           DAT_2008a8a8 * 0x1d8,3);
                                                      (&DAT_200a7aac)[iVar8 * 0x76] = iVar7;
                                                      pbVar6 = (byte *)FUN_20004574((char *)pbVar6,
                                                                                    (char *)&
                                                  local_338,0x200);
                                                  (&DAT_200a7aa8)[DAT_2008a8a8 * 0x76] = 0;
                                                  DAT_2008bfdc = 0;
                                                  while (local_338 != 0x40) {
                                                    DAT_2008a8b0 = 0;
                                                    iVar8 = DAT_20090a78;
                                                    if (true) {
                                                      while ((iVar8 != -1 &&
                                                             (DAT_2008a8b0 = DAT_2008a8b0 + 1,
                                                             DAT_2008a8b0 < 0x100))) {
                                                        iVar8 = (&DAT_20090a78)[DAT_2008a8b0 * 0x5c]
                                                        ;
                                                      }
                                                    }
                                                    if ((((local_338 == 0x67) || (local_338 == 0x72)
                                                         ) || (local_338 == 0x2e)) ||
                                                       (local_338 == 0x2f)) {
                                                      (&DAT_20090a78)[DAT_2008a8b0 * 0x5c] =
                                                           DAT_2008a8b0;
                                                      (&DAT_20090a6c)[DAT_2008a8b0 * 0x5c] = 0;
                                                      (&DAT_200a7b78)
                                                      [DAT_2008a8a8 * 0x76 + DAT_2008bfdc] =
                                                           DAT_2008a8b0;
                                                      (&DAT_200a7aa8)[DAT_2008a8a8 * 0x76] =
                                                           (&DAT_200a7aa8)[DAT_2008a8a8 * 0x76] + 1;
                                                      DAT_2008bfdc = DAT_2008bfdc + 1;
                                                      (&DAT_200a7b78)
                                                      [DAT_2008a8a8 * 0x76 + DAT_2008bfdc] =
                                                           0xffffffff;
                                                      (&DAT_20090ab4)[DAT_2008a8b0 * 0x170] =
                                                           local_338;
                                                      (&DAT_20090ab5)[DAT_2008a8b0 * 0x170] =
                                                           local_336;
                                                      (&DAT_20090ab6)[DAT_2008a8b0 * 0x170] =
                                                           local_335;
                                                      pbVar3 = atoi(abStack_333,(int *)&local_28);
                                                      (&DAT_20090ab0)[DAT_2008a8b0 * 0x170] =
                                                           (char)local_28;
                                                      if (((&DAT_200a7a6c)[DAT_2008a8a8 * 0x1d8] ==
                                                           'M') && (DAT_20072240 < local_28)) {
                                                        DAT_20072240 = local_28;
                                                      }
                                                      (&DAT_20090ad8)[DAT_2008a8b0 * 0x170] = 0x23;
                                                      DAT_2008c1a8 = 1;
                                                      utoa((int)(&DAT_20090ad9 +
                                                                DAT_2008a8b0 * 0x170),3,
                                                           DAT_2008bfdc - 1);
                                                      DAT_2008c1a8 = DAT_2008c1a8 + 3;
                                                      local_138 = 0x78786c;
                                                      (&DAT_20090ab7)[DAT_2008a8b0 * 0x170] = 0x6c;
                                                      (&DAT_20090ab8)[DAT_2008a8b0 * 0x170] = 0x78;
                                                      (&DAT_20090ab9)[DAT_2008a8b0 * 0x170] = 0x78;
                                                      pbVar3 = pbVar3 + 1;
                                                      (&DAT_20090a68)[DAT_2008a8b0 * 0x5c] = 0;
                                                      iVar8 = 3;
                                                      while (*pbVar3 != 0x21) {
                                                        if (*pbVar3 == 0x2c) {
                                                          pbVar3 = pbVar3 + 1;
                                                        }
                                                        if (true) {
                                                          switch(*pbVar3) {
                                                          case 0x68:
                                                            if (pbVar3[1] == 0x2d) {
                                                              (&DAT_20090a88)[DAT_2008a8b0 * 0x5c] =
                                                                   0;
                                                            }
                                                            else {
                                                              atoi(pbVar3 + 1,(int *)&local_28);
                                                              (&DAT_20090a88)[DAT_2008a8b0 * 0x5c] =
                                                                   local_28;
                                                            }
                                                            bVar2 = *pbVar3;
                                                            while (bVar2 != 0x2c) {
                                                              (&DAT_20090ab7)
                                                              [DAT_2008a8b0 * 0x170 + iVar8] =
                                                                   *pbVar3;
                                                              iVar8 = iVar8 + 1;
                                                              pbVar3 = pbVar3 + 1;
                                                              bVar2 = *pbVar3;
                                                            }
                                                            break;
                                                          case 0x77:
                                                            if (pbVar3[1] == 0x2d) {
                                                              (&DAT_20090a84)[DAT_2008a8b0 * 0x5c] =
                                                                   0;
                                                            }
                                                            else {
                                                              atoi(pbVar3 + 1,(int *)&local_28);
                                                              (&DAT_20090a84)[DAT_2008a8b0 * 0x5c] =
                                                                   local_28;
                                                            }
                                                            bVar2 = *pbVar3;
                                                            while (bVar2 != 0x2c) {
                                                              (&DAT_20090ab7)
                                                              [DAT_2008a8b0 * 0x170 + iVar8] =
                                                                   *pbVar3;
                                                              iVar8 = iVar8 + 1;
                                                              pbVar3 = pbVar3 + 1;
                                                              bVar2 = *pbVar3;
                                                            }
                                                            break;
                                                          case 0x78:
                                                            if (pbVar3[1] == 0x2d) {
                                                              (&DAT_20090a7c)[DAT_2008a8b0 * 0x5c] =
                                                                   0;
                                                            }
                                                            else {
                                                              atoi(pbVar3 + 1,(int *)&local_28);
                                                              (&DAT_20090a7c)[DAT_2008a8b0 * 0x5c] =
                                                                   local_28;
                                                            }
                                                            bVar2 = *pbVar3;
                                                            while (bVar2 != 0x2c) {
                                                              (&DAT_20090ab7)
                                                              [DAT_2008a8b0 * 0x170 + iVar8] =
                                                                   *pbVar3;
                                                              iVar8 = iVar8 + 1;
                                                              pbVar3 = pbVar3 + 1;
                                                              bVar2 = *pbVar3;
                                                            }
                                                            break;
                                                          case 0x79:
                                                            if (pbVar3[1] == 0x2d) {
                                                              (&DAT_20090a80)[DAT_2008a8b0 * 0x5c] =
                                                                   0;
                                                            }
                                                            else {
                                                              atoi(pbVar3 + 1,(int *)&local_28);
                                                              (&DAT_20090a80)[DAT_2008a8b0 * 0x5c] =
                                                                   local_28;
                                                            }
                                                            bVar2 = *pbVar3;
                                                            while (bVar2 != 0x2c) {
                                                              (&DAT_20090ab7)
                                                              [DAT_2008a8b0 * 0x170 + iVar8] =
                                                                   *pbVar3;
                                                              iVar8 = iVar8 + 1;
                                                              pbVar3 = pbVar3 + 1;
                                                              bVar2 = *pbVar3;
                                                            }
                                                          }
                                                        }
                                                      }
                                                      iVar8 = 0;
                                                      if (*pbVar3 != 0x3c) {
                                                        iVar8 = 0;
                                                        do {
                                                          (&DAT_20090acc)
                                                          [DAT_2008a8b0 * 0x170 + iVar8] = *pbVar3;
                                                          iVar8 = iVar8 + 1;
                                                          (&DAT_20090acd)
                                                          [DAT_2008a8b0 * 0x170 + iVar8] = 0;
                                                          pbVar3 = pbVar3 + 1;
                                                        } while (*pbVar3 != 0x3c);
                                                      }
                                                      do {
                                                        while (pbVar5 = pbVar3, *pbVar5 != 0x3e) {
                                                          if ((((&DAT_200a7a6c)
                                                                [DAT_2008a8a8 * 0x1d8] == 'S') &&
                                                              (*pbVar5 == 0x26)) &&
                                                             (pbVar5[1] == 0x73)) {
                                                            (&DAT_200a7aa0)[DAT_2008a8a8 * 0x1d8] =
                                                                 pbVar5[2];
                                                          }
                                                          if (((((*pbVar5 == 0x26) &&
                                                                (pbVar5[3] != 0x20)) &&
                                                               (pbVar5[3] != 0x3e)) &&
                                                              ((pbVar5[3] != 0x7e &&
                                                               (pbVar5[3] != 0x5e)))) &&
                                                             (pbVar5[3] != 0x2b)) {
                                                            if (pbVar5[3] == 0x23) {
                                                              (&DAT_20090a68)[DAT_2008a8b0 * 0x5c] =
                                                                   0;
                                                              (&DAT_20090ad8)
                                                              [DAT_2008a8b0 * 0x170 + DAT_2008c1a8]
                                                                   = *pbVar5;
                                                              (&DAT_20090ad9)
                                                              [DAT_2008a8b0 * 0x170 + DAT_2008c1a8]
                                                                   = pbVar5[1];
                                                              *(byte *)(DAT_2008a8b0 * 0x170 +
                                                                        DAT_2008c1a8 + 0x20090ada) =
                                                                   pbVar5[2];
                                                              *(byte *)(DAT_2008a8b0 * 0x170 +
                                                                        DAT_2008c1a8 + 0x20090adb) =
                                                                   pbVar5[4];
                                                              DAT_2008c1a8 = DAT_2008c1a8 + 4;
                                                              iVar8 = iVar8 + 4;
                                                              pbVar3 = pbVar5 + 5;
                                                            }
                                                            else {
                                                              (&DAT_20090a68)[DAT_2008a8b0 * 0x5c] =
                                                                   1;
                                                              (&DAT_20090aa0)[DAT_2008a8b0 * 0x170]
                                                                   = pbVar5[3];
                                                              (&DAT_20090ad8)
                                                              [DAT_2008a8b0 * 0x170 + DAT_2008c1a8]
                                                                   = *pbVar5;
                                                              (&DAT_20090ad9)
                                                              [DAT_2008a8b0 * 0x170 + DAT_2008c1a8]
                                                                   = pbVar5[1];
                                                              *(byte *)(DAT_2008a8b0 * 0x170 +
                                                                        DAT_2008c1a8 + 0x20090ada) =
                                                                   pbVar5[2];
                                                              DAT_2008c1a8 = DAT_2008c1a8 + 3;
                                                              iVar8 = iVar8 + 3;
                                                              pbVar3 = pbVar5 + 4;
                                                            }
                                                          }
                                                          else if (*pbVar5 == 0) {
                                                            pbVar3 = pbVar5 + 1;
                                                          }
                                                          else if (iVar8 == 0xfe) {
                                                            bVar2 = *pbVar5;
                                                            while (pbVar3 = pbVar5, bVar2 != 0x3e) {
                                                              pbVar5 = pbVar5 + 1;
                                                              bVar2 = *pbVar5;
                                                            }
                                                          }
                                                          else {
                                                            (&DAT_20090ad8)
                                                            [DAT_2008a8b0 * 0x170 + DAT_2008c1a8] =
                                                                 *pbVar5;
                                                            DAT_2008c1a8 = DAT_2008c1a8 + 1;
                                                            iVar8 = iVar8 + 1;
                                                            pbVar3 = pbVar5 + 1;
                                                          }
                                                        }
                                                        (&DAT_20090ad8)
                                                        [DAT_2008a8b0 * 0x170 + DAT_2008c1a8] =
                                                             *pbVar5;
                                                        DAT_2008c1a8 = DAT_2008c1a8 + 1;
                                                        pbVar3 = pbVar5 + 1;
                                                      } while (*pbVar3 == 0x3c);
                                                      if (*pbVar3 == 0x2c) {
                                                        pbVar3 = atoi(pbVar5 + 2,(int *)&local_28);
                                                        (&DAT_20090a8c)[DAT_2008a8b0 * 0x5c] =
                                                             local_28;
                                                        pbVar3 = atoi(pbVar3 + 1,(int *)&local_28);
                                                        (&DAT_20090a90)[DAT_2008a8b0 * 0x5c] =
                                                             local_28;
                                                      }
                                                      else {
                                                        (&DAT_20090a8c)[DAT_2008a8b0 * 0x5c] = 0;
                                                      }
                                                      if (*pbVar3 == 0x40) break;
                                                      pbVar6 = (byte *)FUN_20004574((char *)pbVar6,
                                                                                    (char *)&
                                                  local_338,0x200);
                                                  }
                                                  else {
                                                    pbVar6 = (byte *)FUN_20004574((char *)pbVar6,
                                                                                  (char *)&local_338
                                                                                  ,0x200);
                                                  }
                                                  }
                                                  (&DAT_200a7a68)[DAT_2008a8a8 * 0x76] =
                                                       DAT_2008a8a8;
                                                  DAT_2008bfdc = DAT_2008bfdc + 1;
                                                  (&DAT_200a7b78)
                                                  [DAT_2008a8a8 * 0x76 + DAT_2008bfdc] = 0xffffffff;
                                                  uVar17 = 0;
                                                  g_dwCfgTotalWidthDlmx = 0;
                                                  if (g_dwCfgChannels != 0) {
                                                    do {
                                                      g_dwCfgTotalWidthDlmx =
                                                           (&g_dwCfgChannelLengths)[uVar17] +
                                                           g_dwCfgTotalWidthDlmx;
                                                      uVar17 = uVar17 + g_dwCfgColours;
                                                    } while (uVar17 < g_dwCfgChannels);
                                                  }
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    g_dwCfgArabicLigaturesEnabled = 1;
                                                    uVar17 = 0;
                                                    while ((uVar17 < DAT_20031800 &&
                                                           (*pbVar3 != 0x2c))) {
                                                      pbVar3 = (byte *)FUN_200044b8(pbVar3,(int *)&
                                                  local_28);
                                                  iVar8 = g_dwArabicLigatureCount * 3;
                                                  (&DAT_205591f0)[iVar8 + uVar17] = (char)local_28;
                                                  uVar17 = uVar17 + 1;
                                                  (&DAT_205591f0)[iVar8 + uVar17] = 0;
                                                  if (*pbVar3 == 0x20) {
                                                    pbVar3 = pbVar3 + 1;
                                                  }
                                                  }
                                                  pbVar3 = pbVar3 + 1;
                                                  g_dwArabicLigatureCount =
                                                       g_dwArabicLigatureCount + 1;
                                                  uVar17 = 0;
                                                  while (((uVar17 < DAT_20031800 &&
                                                          (*pbVar3 != 0x2c)) &&
                                                         (((0x40 < *pbVar3 && (*pbVar3 < 0x46)) ||
                                                          ((0x2f < *pbVar3 && (*pbVar3 < 0x3a)))))))
                                                  {
                                                    pbVar3 = (byte *)FUN_200044b8(pbVar3,(int *)&
                                                  local_28);
                                                  iVar8 = g_dwArabicLigatureCount * 3;
                                                  (&DAT_205591f0)[iVar8 + uVar17] = (char)local_28;
                                                  uVar17 = uVar17 + 1;
                                                  (&DAT_205591f0)[iVar8 + uVar17] = 0;
                                                  if (*pbVar3 == 0x20) {
                                                    pbVar3 = pbVar3 + 1;
                                                  }
                                                  }
                                                  g_dwArabicLigatureCount =
                                                       g_dwArabicLigatureCount + 1;
                                                  }
                                                  }
                                                  else {
                                                    atoi(pbVar3,(int *)&local_28);
                                                    g_dwCfgEdfMaxTrains = local_28;
                                                  }
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x4e) {
                                                    g_dwCfgEdfAlwaysDefault = 0;
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x59) {
                                                    g_dwCfgEdfAlwaysDefault = 1;
                                                  }
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x4e) {
                                                    g_dwCfgSuppressMonLz = 0;
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x59) {
                                                    g_dwCfgSuppressMonLz = 1;
                                                  }
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x4e) {
                                                    g_dwCfgReplaceHoursLz = 0;
                                                  }
                                                  else if ((*pbVar3 & 0x5f) == 0x59) {
                                                    g_dwCfgReplaceHoursLz = 1;
                                                  }
                                                }
                                                else if ((*pbVar3 & 0x5f) == 0x4e) {
                                                  g_dwCfgSuppressDayLz = 0;
                                                }
                                                else if ((*pbVar3 & 0x5f) == 0x59) {
                                                  g_dwCfgSuppressDayLz = 1;
                                                }
                                              }
                                              else if ((*pbVar3 & 0x5f) == 0x4e) {
                                                g_dwCfgSuppressSecsLz = 0;
                                              }
                                              else if ((*pbVar3 & 0x5f) == 0x59) {
                                                g_dwCfgSuppressSecsLz = 1;
                                              }
                                            }
                                            else if ((*pbVar3 & 0x5f) == 0x4e) {
                                              g_dwCfgSuppressMinsLz = 0;
                                            }
                                            else if ((*pbVar3 & 0x5f) == 0x59) {
                                              g_dwCfgSuppressMinsLz = 1;
                                            }
                                          }
                                          else if ((*pbVar3 & 0x5f) == 0x4e) {
                                            g_dwCfgSuppressHourLz = 0;
                                          }
                                          else if ((*pbVar3 & 0x5f) == 0x59) {
                                            g_dwCfgSuppressHourLz = 1;
                                          }
                                        }
                                        else {
                                          if ((*pbVar3 & 0x5f) == 0x4e) {
                                            g_dwCfgTruncateOnWord = 0;
                                          }
                                          else if ((*pbVar3 & 0x5f) == 0x59) {
                                            g_dwCfgTruncateOnWord = 1;
                                          }
                                          g_dwCfgTruncateOnChar = 0;
                                          g_dwCfgScrollIfTooWide =
                                               (uint)(g_dwCfgTruncateOnWord == 0);
                                        }
                                      }
                                      else {
                                        if ((*pbVar3 & 0x5f) == 0x4e) {
                                          g_dwCfgTruncateOnChar = 0;
                                        }
                                        else if ((*pbVar3 & 0x5f) == 0x59) {
                                          g_dwCfgTruncateOnChar = 1;
                                        }
                                        g_dwCfgTruncateOnWord = 0;
                                        g_dwCfgScrollIfTooWide = (uint)(g_dwCfgTruncateOnChar == 0);
                                      }
                                    }
                                    else {
                                      if ((*pbVar3 & 0x5f) == 0x4e) {
                                        g_dwCfgScrollIfTooWide = 0;
                                      }
                                      else if ((*pbVar3 & 0x5f) == 0x59) {
                                        g_dwCfgScrollIfTooWide = 1;
                                      }
                                      g_dwCfgTruncateOnChar = 0;
                                      g_dwCfgTruncateOnWord = (uint)(g_dwCfgScrollIfTooWide == 0);
                                    }
                                  }
                                  else if (true) {
                                    switch(*pbVar3 & 0x5f) {
                                    case 0x49:
                                      g_bCfgDefMsgEffect = 0x49;
                                      break;
                                    case 0x52:
                                      g_bCfgDefMsgEffect = 0x52;
                                      break;
                                    case 0x53:
                                      g_bCfgDefMsgEffect = 0x53;
                                      break;
                                    case 0x55:
                                      g_bCfgDefMsgEffect = 0x55;
                                      break;
                                    case 0x72:
                                      g_bCfgDefMsgEffect = 0x72;
                                      break;
                                    case 0x73:
                                      g_bCfgDefMsgEffect = 0x73;
                                      break;
                                    case 0x75:
                                      g_bCfgDefMsgEffect = 0x75;
                                    }
                                  }
                                }
                                else {
                                  bVar2 = *pbVar3 & 0x5f;
                                  if (bVar2 == 0x4c) {
                                    g_bCfgDefMsgJust = 0x4c;
                                  }
                                  else if (bVar2 == 0x52) {
                                    g_bCfgDefMsgJust = 0x52;
                                  }
                                  else if (bVar2 == 0x43) {
                                    g_bCfgDefMsgJust = 0x43;
                                  }
                                }
                              }
                              else if ((*pbVar3 & 0x5f) == 0x4e) {
                                g_dwCfgHygrosenTempProbe = 0;
                              }
                              else if ((*pbVar3 & 0x5f) == 0x59) {
                                g_dwCfgHygrosenTempProbe = 1;
                              }
                            }
                            else if (true) {
                              switch(*pbVar3 & 0x5f) {
                              case 0x49:
                                g_bCfgDefSeqEffect = 0x49;
                                break;
                              case 0x52:
                                g_bCfgDefSeqEffect = 0x52;
                                break;
                              case 0x55:
                                g_bCfgDefSeqEffect = 0x55;
                                break;
                              case 0x56:
                                g_bCfgDefSeqEffect = 0x56;
                                break;
                              case 0x72:
                                g_bCfgDefSeqEffect = 0x72;
                                break;
                              case 0x75:
                                g_bCfgDefSeqEffect = 0x75;
                                break;
                              case 0x76:
                                g_bCfgDefSeqEffect = 0x76;
                              }
                            }
                          }
                          else if (*pcVar4 != '1') {
                            g_dwCfgMainChannel = 2;
                          }
                        }
                        else if ((*pbVar3 & 0x5f) == 0x4e) {
                          g_dwCfgEdfCntDown = 0;
                        }
                        else if ((*pbVar3 & 0x5f) == 0x59) {
                          g_dwCfgEdfCntDown = 1;
                        }
                      }
                      else if ((*pbVar3 & 0x5f) == 0x4e) {
                        g_dwCfgSuccession = 0;
                      }
                      else if ((*pbVar3 & 0x5f) == 0x59) {
                        g_dwCfgSuccession = 1;
                      }
                    }
                    else if ((*pbVar3 & 0x5f) == 0x4e) {
                      g_dwCfgCarryPageContent = 0;
                    }
                    else if ((*pbVar3 & 0x5f) == 0x59) {
                      g_dwCfgCarryPageContent = 1;
                    }
                  }
                  else if ((*pbVar3 & 0x5f) == 0x4e) {
                    g_dwCfgCarryLastLines = 0;
                  }
                  else if ((*pbVar3 & 0x5f) == 0x59) {
                    g_dwCfgCarryLastLines = 1;
                  }
                }
                else if ((*pbVar3 & 0x5f) == 0x4e) {
                  g_dwCfgQueueMsThenSs = 0;
                }
                else if ((*pbVar3 & 0x5f) == 0x59) {
                  g_dwCfgQueueMsThenSs = 1;
                }
              }
              else if ((*pbVar3 & 0x5f) == 0x4e) {
                g_dwCfgClearOldQueue = 0;
              }
              else if ((*pbVar3 & 0x5f) == 0x59) {
                g_dwCfgClearOldQueue = 1;
              }
            }
            else if ((*pbVar3 & 0x5f) == 0x4e) {
              g_dwCfgRepeatDls = 0;
            }
            else if ((*pbVar3 & 0x5f) == 0x59) {
              g_dwCfgRepeatDls = 1;
            }
          }
          else if ((*pbVar3 & 0x5f) == 0x4e) {
            g_dwCfgTranslateArabic = 0;
          }
          else if ((*pbVar3 & 0x5f) == 0x59) {
            g_dwCfgTranslateArabic = 1;
          }
        }
        else if ((*pbVar3 & 0x5f) == 0x4e) {
          g_dwCfgArabicAutoDetect = 0;
        }
        else if ((*pbVar3 & 0x5f) == 0x59) {
          g_dwCfgArabicAutoDetect = 1;
        }
        goto switchD_20008af4_caseD_4a;
      }
      pbVar3 = atoi(pbVar3,(int *)&local_28);
      g_dwCfgDdxFixedPage = local_28;
      if ((pbVar3[1] & 0x5f) == 0x4e) {
        g_dwCfgDdxFixedYn = 0;
      }
      else if ((pbVar3[1] & 0x5f) == 0x59) {
        g_dwCfgDdxFixedYn = 1;
      }
      g_abCfgDdxLineField1 = pbVar3[3];
      g_abCfgDdxLineField2 = pbVar3[5];
      g_abCfgDdxLineField3 = pbVar3[6];
      if (pbVar3[8] == 0x3c) {
        pbVar3 = pbVar3 + 9;
        iVar8 = 0;
        do {
          if ((*pbVar3 == 0xd) && (pbVar3[1] == 10)) {
            g_dwCfgDdxFixedSet = 0;
            break;
          }
          *(byte *)((int)&local_138 + iVar8) = *pbVar3;
          pbVar3 = pbVar3 + 1;
          if (*pbVar3 == 0x3e) {
            *(undefined1 *)((int)&local_138 + iVar8 + 1) = 0;
            g_dwCfgDdxFixedSet = 1;
            local_38 = &DAT_2008a720;
            local_34 = 0;
            local_30 = 0x100;
            cmd_flags = 0;
            markup_compile((byte *)&local_138,(int *)&local_38,1);
            break;
          }
          iVar8 = iVar8 + 1;
        } while (iVar8 != 0xff);
      }
    } while( true );
  }
  bVar1 = false;
LAB_2000b880:
  DAT_20072240 = 0;
  if (g_dwCfgChannels == 0) goto LAB_2000b590;
  uVar15 = 0;
  do {
    (&g_dwCfgLinesPerChannel)[uVar15] = g_dwCfgPixels;
    uVar15 = uVar15 + 1;
  } while (uVar15 < g_dwCfgChannels);
LAB_2000b550:
  if (g_dwCfgChannels != 0) {
    uVar15 = 0;
    do {
      if (DAT_20031818 < (uint)(&g_dwCfgChannelLengths)[uVar15]) {
        DAT_20031818 = (&g_dwCfgChannelLengths)[uVar15];
      }
      uVar15 = uVar15 + 1;
    } while (uVar15 < g_dwCfgChannels);
  }
LAB_2000b590:
  switch(DAT_20031818) {
  case 1:
    DAT_20031814 = 0x800;
    break;
  case 2:
    DAT_20031814 = 0x400;
    break;
  case 3:
  case 4:
    DAT_20031814 = 0x200;
    break;
  case 5:
  case 6:
  case 7:
  case 8:
    DAT_20031814 = 0x100;
    break;
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
    DAT_20031814 = 0x80;
  }
  if ((char)g_drive_type == 'M') {
    uVar15 = g_dwCfgPixels + 0x7f;
    if (g_dwCfgChannels != 0) {
      uVar10 = 0;
      do {
        (&DAT_2008c188)[uVar10] = uVar15 & 0xffffff80;
        uVar10 = uVar10 + 1;
      } while (uVar10 < g_dwCfgChannels);
    }
  }
  else if ((((char)g_drive_type == 'T') || ((char)g_drive_type == 'D')) &&
          (uVar15 = g_dwCfgPixels + 0x1f, g_dwCfgChannels != 0)) {
    uVar10 = 0;
    do {
      (&DAT_2008c188)[uVar10] = uVar15 & 0xffffffe0;
      uVar10 = uVar10 + 1;
    } while (uVar10 < g_dwCfgChannels);
  }
  if (g_dwCfgColours == 2) {
    DAT_20072210 = DAT_20031814 * DAT_20031818 * g_dwCfgRowsPerLine * 4 >> 3;
    DAT_20072214 = 0;
  }
  else if (g_dwCfgColours == 3) {
    DAT_20072210 = DAT_20031814 * g_dwCfgRowsPerLine * DAT_20031818 * 2 >> 3;
    DAT_20072214 = DAT_20031814 * g_dwCfgRowsPerLine * DAT_20031818 * 4 >> 3;
  }
  else if (g_dwCfgColours == 1) {
    DAT_20072210 = 0;
    DAT_20072214 = 0;
  }
  if (!bVar1) {
    g_dwCfgDdxModalV1 = 0;
    g_dwCfgDdxModalV2 = 0;
    g_dwCfgDdxModalV4 = g_dwCfgPixels;
    g_dwCfgDdxModalV3 = g_dwCfgTotalWidthDlmx * g_dwCfgRowsPerLine;
  }
  FUN_20007900();
  DAT_20031904 = DAT_20031904 & 0xff;
  if (9 < DAT_20031904) {
    DAT_20031904 = 4;
  }
  FUN_20007a04(DAT_20031904,extraout_r1);
  FUN_2000441c();
  DAT_200722b4 = 0;
  DAT_20072398 = 0;
  return;
LAB_2000b4d4:
  DAT_20072240 = 0;
  if (uVar10 == 0) goto LAB_2000b880;
  if (g_dwCfgChannels == 0) goto LAB_2000b590;
  uVar15 = 0;
  do {
    if (g_dwCfgPixels < (uint)(&g_dwCfgLinesPerChannel)[uVar15]) {
      g_dwCfgPixels = (&g_dwCfgLinesPerChannel)[uVar15];
    }
    uVar15 = uVar15 + 1;
  } while (uVar15 < g_dwCfgChannels);
  goto LAB_2000b550;
}

