
/* WARNING: Inlined function: memcmp */

byte * command_parse(byte *param_1)

{
  int iVar1;
  uint uVar2;
  ushort uVar3;
  ulonglong uVar4;
  uint5 uVar5;
  byte *pbVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  char *pcVar10;
  dword dVar11;
  byte *pbVar12;
  undefined4 extraout_r1;
  undefined *puVar13;
  undefined1 *src;
  uint uVar14;
  undefined4 uVar15;
  uint uVar16;
  byte *pbVar17;
  byte bVar18;
  int iVar19;
  undefined *puVar20;
  uint uVar21;
  uint uVar22;
  int *piVar23;
  byte bVar24;
  undefined *puVar25;
  undefined *puVar26;
  int *piVar27;
  uint *puVar28;
  byte *pbVar29;
  byte *pbVar30;
  uint *dst;
  uint uVar31;
  char cVar32;
  int iVar33;
  bool bVar34;
  ulonglong uVar35;
  uint uStack_2005c;
  uint uStack_20058;
  int iStack_20054;
  int iStack_20050;
  uint uStack_2004c;
  int *piStack_20040;
  undefined4 uStack_2003c;
  undefined4 uStack_20038;
  undefined4 uStack_20034;
  int iStack_20030;
  byte abStack_20027 [131055];
  undefined1 *local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint local_28;
  
  cmd_flags = 0;
  g_dwCmdErrorCode = 0;
  pbVar6 = (byte *)0x5018;
  DAT_200815e4 = param_1 + 0x5018;
  param_1[0x5018] = 0;
  if (DAT_200909ac == 0) {
    pbVar17 = param_1 + 0x12;
    pbVar6 = param_1;
    if (DAT_20072280 == 0) {
      if (g_protocol_3 == 0) {
        uVar22 = FUN_20012f80((int)param_1);
        if (uVar22 == 0) {
          return (byte *)0x0;
        }
        uVar22 = *(uint *)(param_1 + 8);
        if ((4 < uVar22) && (pbVar6 = param_1 + 0x10, param_1[uVar22 + 0xd] == 0x2f)) {
          param_1[uVar22 + 0xd] = 0;
          *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -3;
          if (uVar22 == 3) {
            uVar21 = 0x5b;
          }
          else {
            uVar21 = 0x5b;
            uVar16 = uVar22;
            do {
              uVar21 = uVar21 + *pbVar6;
              uVar16 = uVar16 - 1;
              pbVar6 = pbVar6 + 1;
            } while (uVar16 != 3);
            pbVar6 = param_1 + uVar22 + 0xd;
          }
          pbVar6 = (byte *)decode_hex_byte(pbVar6 + 1);
          if ((byte *)(uVar21 & 0xff) != pbVar6) {
            cmd_flags = cmd_flags | 0x20;
            return pbVar6;
          }
        }
      }
      else {
        g_dwFfpReplyEnabled = 0;
        if (*(uint *)(param_1 + 8) < 2) {
          g_dwFfpReplyEnabled = 0;
          return param_1;
        }
        uVar22 = read_dip_switches();
        DAT_200815dd = (byte)(uVar22 & 0x7f);
        if ((uVar22 & 0x7f) == 0) {
          DAT_200815dd = 1;
        }
        pbVar6 = param_1 + 0x10;
        uVar22 = decode_hex_byte(pbVar6);
        g_dwFfpReplyEnabled = (uint)((byte *)(uint)DAT_200815dd == (byte *)(uVar22 & 0xff));
        if (g_dwFfpReplyEnabled == 0) {
          return (byte *)(uVar22 & 0xff);
        }
        if (2 < *(uint *)(param_1 + 8)) {
          bVar18 = param_1[0x10];
          if (bVar18 == 3) {
            cVar32 = '\x01';
          }
          else {
            cVar32 = '\x01';
            do {
              cVar32 = cVar32 + bVar18;
              pbVar6 = pbVar6 + 1;
              bVar18 = *pbVar6;
            } while (bVar18 != 3);
          }
          *pbVar6 = 0;
          if ((param_1[0x5090] != 0xaa) && (param_1[0x5090] != (byte)(cVar32 + 3U))) {
            cmd_flags = cmd_flags | 0x20;
            pbVar6 = (byte *)FUN_2000e62c(param_1,0);
            return pbVar6;
          }
        }
      }
      pbVar6 = (byte *)cmd_d_raw_handler();
      if (g_protocol_3 != 0) {
        pbVar6 = (byte *)FUN_2000e62c(param_1,1);
      }
      if (DAT_2007236c == 0) {
        if (DAT_20072414 != 0) {
          DAT_20072364 = DAT_20072364 | 8;
        }
        DAT_20072414 = 0;
      }
    }
    if (param_1[2] == 1) {
      if (DAT_20072414 != 0) {
        cmd_flags = cmd_flags | 1;
        return pbVar6;
      }
      pbVar6 = (byte *)FUN_2000441c();
    }
    else if (param_1[2] == 2) {
      DAT_20072414 = 1;
      DAT_20072364 = DAT_20072364 | 0x10;
      DAT_2007236c = g_dwCfgMaintTime * 60000;
    }
  }
  else {
    pbVar17 = DAT_2053f2e0;
    if (DAT_20072280 != 0) {
      pbVar6 = param_1;
      pbVar17 = param_1 + 0x12;
    }
  }
  uVar35 = ZEXT48(pbVar6);
  g_dwSlotSkipBody = 0;
  DAT_200855ec = (byte *)0x0;
  uStack_20058 = 0;
  iStack_20054 = 0;
  do {
    pbVar6 = (byte *)uVar35;
    if (*pbVar17 == 0) {
      if (g_dwSlotSkipBody == 0) {
        if (((g_protocol_1 != 0) || (g_protocol_4 != 0)) && (g_dwActivePageIdx != 0xffffffff)) {
          pbVar6 = (byte *)FUN_2000f120();
        }
        if ((g_protocol_2 != 0) && (g_dwActivePageIdx != 0xffffffff)) {
          pbVar6 = (byte *)page_render_teardown();
        }
      }
      else {
        uStack_20038 = 0x2d4d5241;
        uStack_20034 = 0x47534d41;
        if (*DAT_200855ec == 0) {
          iVar33 = 0x11;
          DAT_200855ec = DAT_200855ec + 1;
        }
        else {
          iVar33 = 0x11;
          pbVar6 = DAT_200855ec + 1;
          pbVar17 = DAT_200855ec + 2;
          do {
            DAT_200855ec = pbVar17;
            *(byte *)((int)&uStack_20038 + iVar33) = *pbVar6;
            iVar33 = iVar33 + 1;
            pbVar6 = DAT_200855ec;
            pbVar17 = DAT_200855ec + 1;
          } while (DAT_200855ec[-1] != 0);
        }
        *(undefined1 *)((int)&uStack_20038 + iVar33 + -1) = 0xd;
        *(undefined1 *)((int)&uStack_20038 + iVar33) = 10;
        *(undefined1 *)((int)&uStack_20038 + iVar33 + 1) = 0x2e;
        *(undefined1 *)((int)&uStack_20038 + iVar33 + 2U) = 0xff;
        *(undefined1 *)((int)&uStack_20038 + iVar33 + 3) = 0;
        iStack_20030 = iVar33 + -0xd;
        pbVar6 = (byte *)FUN_200019fc(8,(int)&uStack_20038,iVar33 + 2U);
        g_dwActivePageIdx = 0xffffffff;
        g_dwSlotSkipBody = 0;
      }
      return pbVar6;
    }
    if (cmd_flags != 0) {
      return pbVar6;
    }
    pbVar6 = pbVar17;
    if (((DAT_200909ac == 0) && (g_protocol_3 != 0)) && (DAT_20072280 == 0)) {
      if (DAT_20031860 != 0) {
        if ((g_dwCfgEdfAlwaysDefault == 0) && (DAT_20031870 != 0)) {
          puVar25 = &DAT_2053f4a8;
          uVar22 = 0;
          do {
            cVar32 = puVar25[0xec];
            if ((cVar32 == 'M' || cVar32 == 'S') || (cVar32 == 'D')) {
              page_slot_set_active(uVar22,0);
            }
            uVar22 = uVar22 + 1;
            puVar25 = puVar25 + 0xfc;
          } while (uVar22 < DAT_20031870);
        }
        uVar22 = cmd_d_raw_handler();
        uVar35 = (ulonglong)uVar22;
        DAT_20031860 = 0;
      }
      uVar22 = (uint)uVar35;
      pbVar30 = pbVar17 + 1;
      pbVar6 = pbVar30;
      if (true) {
        switch(*pbVar17) {
        case 0x52:
          if (*pbVar30 == 0x78 || *pbVar30 == 2) {
            pbVar6 = pbVar17 + 2;
            iVar33 = FUN_2000c214((char *)pbVar6,"Time Now ",9);
            if ((iVar33 == 0) && (iVar33 = FUN_2000c214((char *)pbVar6,"TIME NOW ",9), iVar33 == 0))
            {
              iVar33 = FUN_2000c214((char *)pbVar6,"Date Now ",9);
              if ((iVar33 == 0) &&
                 (iVar33 = FUN_2000c214((char *)pbVar6,"DATE NOW ",9), iVar33 == 0)) {
                iVar33 = FUN_2000c214((char *)pbVar6,"TEMPERATURE NOW ",0x10);
                if (((iVar33 == 0) &&
                    (iVar33 = FUN_2000c214((char *)pbVar6,"Temperature Now ",0x10), iVar33 == 0)) &&
                   (iVar33 = FUN_2000c214((char *)pbVar6,"Temp Now ",9), iVar33 == 0)) {
                  uVar22 = FUN_2000c214((char *)pbVar6,"TEMP NOW ",9);
                  uVar35 = (ulonglong)uVar22;
                  if (uVar22 == 0) break;
                }
                uVar22 = FUN_2000c214((char *)pbVar6,"TEMPERATURE NOW ",0x10);
                if ((uVar22 == 0) &&
                   (uVar22 = FUN_2000c214((char *)pbVar6,"Temperature Now ",0x10), uVar22 == 0)) {
                  pbVar6 = pbVar17 + 0xb;
                }
                else {
                  pbVar6 = pbVar17 + 0x12;
                }
                bVar18 = *pbVar6;
                if ((bVar18 == 0x20 || bVar18 == 0x2b) ||
                   (uVar35 = (ulonglong)uVar22, bVar18 == 0x2d)) {
                  uVar22 = parse_digits(pbVar6 + 1,2);
                  uVar35 = (ulonglong)uVar22;
                  if (uVar22 != 0xffffffff) {
                    DAT_20031864 = *pbVar6;
                    DAT_20072258 = 1;
                    pbVar6 = pbVar6 + 3;
                    uVar35 = (ulonglong)uVar22;
                    DAT_20072244 = uVar22;
                  }
                }
              }
              else {
                pbVar6 = pbVar17 + 0xb;
                uVar22 = parse_digits(pbVar6,2);
                uVar35 = (ulonglong)uVar22;
                if (uVar22 != 0xffffffff) {
                  uVar21 = parse_digits(pbVar17 + 0xe,2);
                  uVar35 = (ulonglong)uVar21;
                  if (uVar21 != 0xffffffff) {
                    uVar16 = parse_digits(pbVar17 + 0x11,2);
                    uVar35 = (ulonglong)uVar16;
                    if (((uVar16 != 0xffffffff) && (uVar35 = (ulonglong)uVar16, uVar21 - 1 < 0xc))
                       && (uVar35 = (ulonglong)uVar16, uVar21 != 0)) {
                      uVar8 = FUN_20001470(uVar21,uVar16);
                      uVar35 = (ulonglong)uVar8;
                      if (uVar22 <= uVar8) {
                        iVar33 = FUN_200014bc(uVar22,uVar21,uVar16);
                        iVar7 = FUN_20001528(uVar22);
                        g_rtc_month = (byte)iVar7;
                        iVar7 = FUN_20001528(uVar21);
                        g_rtc_day_of_month = (byte)iVar7;
                        iVar7 = FUN_20001528(uVar16);
                        g_rtc_year = (byte)iVar7;
                        g_rtc_day_of_week = (byte)iVar33;
                        uVar22 = FUN_2000ee98(0);
                        pbVar6 = pbVar17 + 0x13;
                        uVar35 = (ulonglong)uVar22;
                      }
                    }
                  }
                }
              }
            }
            else {
              pbVar6 = pbVar17 + 0xb;
              uVar22 = parse_digits(pbVar6,2);
              uVar35 = (ulonglong)uVar22;
              if (uVar22 != 0xffffffff) {
                uVar21 = parse_digits(pbVar17 + 0xe,2);
                uVar35 = (ulonglong)uVar21;
                if (uVar21 != 0xffffffff) {
                  uVar16 = parse_digits(pbVar17 + 0x11,2);
                  uVar35 = (ulonglong)uVar16;
                  if ((((uVar16 != 0xffffffff) && (uVar35 = (ulonglong)uVar16, uVar22 < 0x18)) &&
                      (uVar35 = (ulonglong)uVar16, uVar21 < 0x3c)) &&
                     (uVar35 = (ulonglong)uVar16, uVar16 < 0x3c)) {
                    iVar33 = FUN_20001528(uVar22);
                    DAT_20031400._3_1_ = (byte)iVar33;
                    iVar33 = FUN_20001528(uVar21);
                    DAT_20031400._2_1_ = (byte)iVar33;
                    iVar33 = FUN_20001528(uVar16);
                    DAT_20031400._1_1_ = (byte)iVar33;
                    uVar22 = FUN_2000ee98(1);
                    if ((g_dwCfgDdxFixedLineSet != 0) && (DAT_2003185c != 0)) {
                      if ((g_dwCfgDoublesided != 0) && (g_protocol_1 == 0)) {
                        g_dwPageNeedsTeardown = 1;
                        FUN_20012208(g_dwCfgDdxFixedLine +
                                     ((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1));
                      }
                      uVar22 = FUN_20012208(g_dwCfgDdxFixedLine);
                    }
                    DAT_2003185c = 0;
                    pbVar6 = pbVar17 + 0x13;
                    uVar35 = (ulonglong)uVar22;
                  }
                }
              }
            }
          }
          break;
        case 0x57:
          uVar35 = (ulonglong)g_dwCfgEdfAlwaysDefault;
          if ((g_dwCfgEdfAlwaysDefault == 0) && (uVar35 = 0, *pbVar30 == 0x2f)) {
            pbVar6 = pbVar17 + 2;
            if ((*pbVar6 == 0x2f) && (pbVar30 = pbVar17 + 3, pbVar17[3] == 0 || pbVar17[3] == 3)) {
              uVar22 = 0;
              if (DAT_20031870 != 0) {
                puVar25 = &DAT_2053f4a8;
                uVar21 = 0;
                do {
                  if (puVar25[0xec] == 'D' || puVar25[0xec] == 'M') {
                    uVar22 = page_slot_set_active(uVar21,0);
                  }
                  uVar21 = uVar21 + 1;
                  puVar25 = puVar25 + 0xfc;
                } while (uVar21 < DAT_20031870);
              }
              iVar33 = 0;
              do {
                pbVar17 = pbVar30;
                uVar35 = CONCAT44(iVar33,uVar22);
                uVar21 = g_dwCfgFxSlowdown;
                if ((&g_dwPageRecScheduleMark)[*(int *)((int)&g_dwPlaylistQueue + iVar33) * 0x3f] !=
                    0) goto switchD_2001632c_caseD_1e;
                iVar33 = iVar33 + 4;
              } while (iVar33 != 400);
              uVar22 = FUN_2002e038();
              pbVar6 = pbVar30;
              uVar35 = (ulonglong)uVar22;
            }
            else {
              uVar22 = FUN_2000c214((char *)pbVar6,"snu",3);
              if (uVar22 == 0) {
                uVar22 = 0;
                if (DAT_2053edf0 == 0) {
                  iVar33 = FUN_200254d4('M');
                  uVar22 = 0;
                  if ((iVar33 != 0) &&
                     (uVar22 = FUN_200274ac('M',0x2a,(int)pbVar6), DAT_2053edf8 != 0)) {
                    uVar22 = FUN_20029828();
                  }
                }
                bVar18 = *pbVar6;
                while (uVar35 = (ulonglong)uVar22, bVar18 != 0) {
                  pbVar6 = pbVar6 + 1;
                  bVar18 = *pbVar6;
                }
              }
              else {
                DAT_2053f2d8._0_1_ = pbVar17[5];
                DAT_2053f2d8._1_1_ = pbVar17[6];
                bVar18 = pbVar17[7];
                bVar24 = pbVar17[8];
                pbVar6 = pbVar17 + 9;
                if (bVar24 == 0x69) {
                  uVar22 = 0;
                  DAT_2053edf0 = 0;
                  uVar35 = 0;
                  if (DAT_20031870 != 0) {
                    puVar25 = &DAT_2053f4a8;
                    uVar21 = 0;
                    do {
                      if (puVar25[0xec] == 'S') {
                        uVar22 = page_slot_set_active(uVar21,0);
                      }
                      uVar21 = uVar21 + 1;
                      puVar25 = puVar25 + 0xfc;
                      uVar35 = (ulonglong)uVar22;
                    } while (uVar21 < DAT_20031870);
                  }
                }
                else {
                  if (bVar24 == 0x43 || bVar24 == 0x50) {
                    if (DAT_20031870 != 0) {
                      puVar25 = &DAT_2053f4a8;
                      uVar21 = 0;
                      do {
                        if ((puVar25[0xec] == 'S') && ((uint)(byte)puVar25[0xf4] == (uint)bVar18)) {
                          uVar22 = page_slot_set_active(uVar21,0);
                        }
                        uVar21 = uVar21 + 1;
                        puVar25 = puVar25 + 0xfc;
                      } while (uVar21 < DAT_20031870);
                    }
                    if (bVar24 == 0x43) {
                      DAT_2053edf0 = 0;
                      iVar33 = 0;
                      do {
                        pbVar17 = pbVar6;
                        uVar35 = CONCAT44(iVar33,uVar22);
                        uVar21 = g_dwCfgFxSlowdown;
                        if ((&g_dwPageRecScheduleMark)
                            [*(int *)((int)&g_dwPlaylistQueue + iVar33) * 0x3f] != 0)
                        goto switchD_2001632c_caseD_1e;
                        iVar33 = iVar33 + 4;
                      } while (iVar33 != 400);
                      uVar22 = FUN_2002e038();
                    }
                  }
                  uVar35 = (ulonglong)uVar22;
                  if (bVar24 == 0x50) {
                    uStack_20038._0_3_ = CONCAT12(bVar18,0x732f);
                    iVar33 = 3;
                    do {
                      bVar24 = *pbVar6;
                      if (bVar24 == 0 || bVar24 == 0x2f) {
                        *(undefined1 *)((int)&uStack_20038 + iVar33) = 0;
                        break;
                      }
                      *(byte *)((int)&uStack_20038 + iVar33) = bVar24;
                      iVar33 = iVar33 + 1;
                      pbVar6 = pbVar6 + 1;
                    } while (iVar33 != 0xffd);
                    *(undefined1 *)((int)&uStack_20038 + iVar33) = 0;
                    uVar22 = FUN_200254d4('S');
                    uVar35 = (ulonglong)uVar22;
                    if (uVar22 != 0) {
                      uVar22 = FUN_200274ac('S',(uint)bVar18,(int)&uStack_20038);
                      uVar35 = (ulonglong)uVar22;
                      if (DAT_2053edf8 != 0) {
                        uVar22 = FUN_20029828();
                        uVar35 = (ulonglong)uVar22;
                      }
                    }
                  }
                }
              }
            }
          }
          break;
        case 0x5a:
          pbVar6 = pbVar17 + 2;
          if (false) {
switchD_20014c90_caseD_45:
            param_1[0x5010] = 0x15;
            param_1[0x5011] = 0x5a;
            param_1[0x5012] = *pbVar6;
            pbVar17 = param_1 + 0x5013;
            bin_to_hex((int)pbVar17,2,(uint)DAT_200815dd);
            strcpy((char *)pbVar17,": code not recognised ");
            *pbVar17 = 0;
            uVar22 = (uint)*param_1;
            USART_tx_string(uVar22,(char *)(param_1 + 0x5010));
            uVar35 = (ulonglong)uVar22;
          }
          else {
            switch(*pbVar30) {
            case 0x42:
              if (*pbVar6 == 0x3f) {
                param_1[0x5010] = 0x5a;
                param_1[0x5011] = 0x42;
                pbVar17 = param_1 + 0x5012;
                bin_to_hex((int)pbVar17,2,(uint)DAT_200815dd);
                strcpy((char *)pbVar17,":");
                pcVar10 = utoa((int)pbVar17,3,DAT_200722a0);
                strcpy(pcVar10,",");
                pcVar10 = utoa((int)pcVar10,3,DAT_200318b4);
                *pcVar10 = '\0';
                uVar22 = (uint)*param_1;
                USART_tx_string(uVar22,(char *)(param_1 + 0x5010));
                uVar35 = (ulonglong)uVar22;
                if (*pbVar6 == 0x3f) break;
              }
              local_28 = 0;
              pbVar6 = atoi(pbVar6,(int *)&local_28);
              uVar35 = ZEXT48(pbVar6);
              if (local_28 < 0x65) {
                DAT_200722a0 = local_28;
              }
              break;
            case 0x43:
              pbVar30 = param_1 + 0x5010;
              pbVar17 = pbVar30;
              strcpy((char *)pbVar30,"ZC");
              bin_to_hex((int)pbVar17,2,(uint)DAT_200815dd);
              strcpy((char *)pbVar17,":");
              bin_to_hex((int)pbVar17,2,DAT_2007235c);
              strcpy((char *)pbVar17,",");
              uVar22 = read_0x6000030();
              bin_to_hex((int)pbVar17,2,uVar22);
              strcpy((char *)pbVar17,",");
              pcVar10 = utoa((int)pbVar17,5,DAT_2007228c);
              *pcVar10 = '\0';
              DAT_2007235c = 0;
              DAT_200318c0 = 0;
              uVar22 = (uint)*param_1;
              USART_tx_string(uVar22,(char *)pbVar30);
              uVar35 = (ulonglong)uVar22;
              break;
            case 0x44:
              g_protocol_5 = 0;
              g_protocol_4 = 0;
              g_protocol_2 = 0;
              g_protocol_3 = 0;
              g_protocol_7 = 0;
              g_protocol_1 = 1;
              mem_init();
              uVar35 = (ulonglong)uVar22;
              g_dwCfgCurrentMode = 1;
              break;
            default:
              goto switchD_20014c90_caseD_45;
            case 0x4c:
              uVar22 = led_test();
              uVar35 = (ulonglong)uVar22;
              break;
            case 0x4f:
              if (*pbVar6 == 0x3f) {
                param_1[0x5010] = 0x5a;
                param_1[0x5011] = 0x4f;
                pbVar6 = param_1 + 0x5012;
                bin_to_hex((int)pbVar6,2,(uint)DAT_200815dd);
                pbVar30 = pbVar6 + 1;
                *pbVar6 = 0x3a;
                bin_to_hex((int)pbVar30,2,g_dwCfgTimeout);
                *pbVar30 = 0;
                uVar22 = (uint)*param_1;
                USART_tx_string(uVar22,(char *)(param_1 + 0x5010));
                uVar35 = (ulonglong)uVar22;
                pbVar6 = pbVar17 + 3;
              }
              else {
                local_28 = 0;
                pbVar6 = atoi(pbVar6,(int *)&local_28);
                g_dwCfgTimeout = local_28;
                uVar22 = FUN_2000441c();
                uVar35 = (ulonglong)uVar22;
              }
              break;
            case 0x50:
              pbVar30 = param_1 + 0x5010;
              pbVar17 = pbVar30;
              strcpy((char *)pbVar30,"ZP");
              bin_to_hex((int)pbVar17,2,(uint)DAT_200815dd);
              strcpy((char *)pbVar17,":");
              uVar22 = read_0x6000030();
              bin_to_hex((int)pbVar17,2,uVar22);
              *pbVar17 = 0;
              uVar22 = (uint)*param_1;
              USART_tx_string(uVar22,(char *)pbVar30);
              uVar35 = (ulonglong)uVar22;
              break;
            case 0x51:
              g_dwCfgCarryLastLines = (uint)(*pbVar6 == 1);
              g_dwCfgQueueMsThenSs = (uint)(pbVar17[4] == 1);
              pbVar6 = pbVar17 + 5;
              break;
            case 0x52:
              uVar22 = system_reset();
              uVar35 = (ulonglong)uVar22;
              break;
            case 0x53:
              param_1[0x5010] = 0x5a;
              param_1[0x5011] = 0x53;
              pbVar17 = param_1 + 0x5012;
              bin_to_hex((int)pbVar17,2,(uint)DAT_200815dd);
              strcpy((char *)pbVar17,": PCB236 UID is ");
              strcpy((char *)pbVar17,&DAT_20031898);
              *pbVar17 = 0;
              uVar22 = (uint)*param_1;
              USART_tx_string(uVar22,(char *)(param_1 + 0x5010));
              uVar35 = (ulonglong)uVar22;
              break;
            case 0x54:
              uVar22 = (uint)*pbVar6;
              if (uVar22 - 0x30 < 8) {
                if (uVar22 == 0x30) {
                  DAT_200722b4 = 0;
                }
                else {
                  DAT_200722b4 = uVar22 - 0x30;
                }
              }
              break;
            case 0x56:
              param_1[0x5010] = 0x5a;
              param_1[0x5011] = 0x56;
              pbVar17 = param_1 + 0x5012;
              local_28 = get_app_version();
              bin_to_hex((int)pbVar17,2,(uint)DAT_200815dd);
              strcpy((char *)pbVar17,":");
              bin_to_hex((int)pbVar17,4,(int)local_28 >> 0x10);
              strcpy((char *)pbVar17,"-");
              bin_to_hex((int)pbVar17,4,local_28 & 0xffff);
              *pbVar17 = 0;
              uVar22 = (uint)*param_1;
              USART_tx_string(uVar22,(char *)(param_1 + 0x5010));
              uVar35 = (ulonglong)uVar22;
              break;
            case 0x5a:
              if (*pbVar6 == 0x3a) {
                pbVar6 = pbVar17 + 3;
                uVar22 = FUN_2000c214(&DAT_20031898,(char *)pbVar6,0xc);
                uVar35 = (ulonglong)uVar22;
                if (uVar22 != 0) {
                  pbVar30 = param_1 + 0x5010;
                  pbVar17 = pbVar30;
                  strcpy((char *)pbVar30,"ZZ");
                  bin_to_hex((int)pbVar17,2,(uint)DAT_200815dd);
                  strcpy((char *)pbVar17,":");
                  uVar22 = read_dip_switches();
                  if ((uVar22 & 0x800) == 0) {
                    strcpy((char *)pbVar17,"9600  N81");
                  }
                  else {
                    strcpy((char *)pbVar17,"19200 N81");
                  }
                  *pbVar17 = 0;
                  USART_tx_string((uint)*param_1,(char *)pbVar30);
                  USART_wait_tx_done((uint)*param_1);
                  gpbr_set_word(0,5);
                  gpbr_set_word(1,(uint)*param_1);
                  uVar22 = read_dip_switches();
                  if ((uVar22 & 0x800) == 0) {
                    uVar15 = 0x2580;
                  }
                  else {
                    uVar15 = 0x4b00;
                  }
                  gpbr_set_word(2,uVar15);
                  uVar22 = system_reset();
                  uVar35 = (ulonglong)uVar22;
                }
              }
            }
          }
          break;
        case 100:
          uVar22 = cmd_d_raw_handler();
          uVar35 = (ulonglong)uVar22;
        }
      }
      pbVar17 = pbVar6;
      uVar21 = g_dwCfgFxSlowdown;
      if (DAT_20072280 != 0) goto parse_mnemonic;
      goto switchD_2001632c_caseD_1e;
    }
parse_mnemonic:
    pbVar30 = DAT_200815e4;
    uVar16 = DAT_2007235c;
    uVar8 = (uint)*pbVar6;
    uVar22 = uVar8;
    pbVar17 = pbVar6;
    while (uVar22 == 0x20) {
      pbVar17 = pbVar17 + 1;
      uVar22 = (uint)*pbVar17;
    }
    if (uVar22 != 0x21) goto LAB_200162b4;
    uVar3 = CONCAT11(pbVar17[1],pbVar17[2]);
    if (uVar3 == 0x7271) {
      uStack_2005c = 0x30042;
    }
    else if (uVar3 < 0x7272) {
      if (uVar3 == 0x3f7a) {
        uStack_2005c = 0x3002a;
      }
      else if (uVar3 < 0x3f7b) {
        if (uVar3 == 0x3f68) {
          uStack_2005c = 0x3002f;
        }
        else if (uVar3 < 0x3f69) {
          if (uVar3 == 0x3f62) {
            uStack_2005c = 0x30023;
          }
          else if (uVar3 < 0x3f63) {
            if (uVar3 == 0x3f46) {
              uStack_2005c = 0x300c0;
            }
            else if (uVar3 == 0x3f61) {
              uStack_2005c = 0x30020;
            }
            else {
              if (uVar3 != 0x3f3f) goto LAB_20015cdc;
              uStack_2005c = 0x3001f;
            }
          }
          else if (uVar3 == 0x3f64) {
            uStack_2005c = 0x30022;
          }
          else if (uVar3 < 0x3f64) {
            uStack_2005c = 0x10026;
          }
          else {
            if (uVar3 != 0x3f65) goto LAB_20015cdc;
            uStack_2005c = 0x3002c;
          }
        }
        else if (uVar3 == 0x3f6e) {
          uStack_2005c = 0x30028;
        }
        else if (uVar3 < 0x3f6f) {
          if (uVar3 == 0x3f6a) {
            uStack_2005c = 0x3002b;
          }
          else if (uVar3 < 0x3f6a) {
            uStack_2005c = 0x10025;
          }
          else {
            if (uVar3 != 0x3f6d) goto LAB_20015cdc;
            uStack_2005c = 0x1002d;
          }
        }
        else if (uVar3 == 0x3f73) {
          uStack_2005c = 0x30024;
        }
        else if (uVar3 < 0x3f74) {
          if (uVar3 != 0x3f6f) goto LAB_20015cdc;
          uStack_2005c = 0x3002e;
        }
        else if (uVar3 == 0x3f74) {
          uStack_2005c = 0x30021;
        }
        else {
          if (uVar3 != 0x3f76) goto LAB_20015cdc;
          uStack_2005c = 0x30029;
        }
      }
      else if (uVar3 == 0x6164) {
        uStack_2005c = 0x3001a;
      }
      else if (uVar3 < 0x6165) {
        if (uVar3 == 0x466d) {
          uStack_2005c = 0x300c5;
        }
        else if (uVar3 < 0x466e) {
          if (uVar3 == 0x447a) {
            uStack_2005c = 0x300bd;
          }
          else if (uVar3 == 0x4640) {
            uStack_2005c = 0x300c3;
          }
          else {
            if (uVar3 != 0x4463) goto LAB_20015cdc;
            uStack_2005c = 0x300bc;
          }
        }
        else if (uVar3 == 0x4678) {
          uStack_2005c = 0x300c2;
        }
        else if (uVar3 == 0x4c53) {
          uStack_2005c = 0x300c4;
        }
        else {
          if (uVar3 != 0x4673) goto LAB_20015cdc;
          uStack_2005c = 0x300c1;
        }
      }
      else if (uVar3 == 0x7262) {
        uStack_2005c = 0x30049;
      }
      else if (uVar3 < 0x7263) {
        if (uVar3 == 0x6b67) {
          uStack_2005c = 0x30091;
        }
        else if (uVar3 == 0x6b74) {
          uStack_2005c = 0x30090;
        }
        else {
          if (uVar3 != 0x6363) goto LAB_20015cdc;
          uStack_2005c = 0x30018;
        }
      }
      else if (uVar3 == 0x7266) {
        uStack_2005c = 0x30043;
      }
      else if (uVar3 < 0x7267) {
        if (uVar3 != 0x7265) goto LAB_20015cdc;
        uStack_2005c = 0x30048;
      }
      else if (uVar3 == 0x726d) {
        uStack_2005c = 0x30046;
      }
      else {
        if (uVar3 != 0x7270) goto LAB_20015cdc;
        uStack_2005c = 0x30040;
      }
    }
    else if (uVar3 == 0x7565) {
      uStack_2005c = 0x30038;
    }
    else if (uVar3 < 0x7566) {
      if (uVar3 == 0x7366) {
        uStack_2005c = 0x30019;
      }
      else if (uVar3 < 0x7367) {
        if (uVar3 == 0x7362) {
          uStack_2005c = 0x30013;
        }
        else if (uVar3 < 0x7363) {
          if (uVar3 == 0x7274) {
            uStack_2005c = 0x30041;
          }
          else if (uVar3 == 0x7361) {
            uStack_2005c = 0x30010;
          }
          else {
            if (uVar3 != 0x7273) goto LAB_20015cdc;
            uStack_2005c = 0x30035;
          }
        }
        else if (uVar3 == 0x7364) {
          uStack_2005c = 0x30012;
        }
        else if (uVar3 < 0x7365) {
          uStack_2005c = 0x10016;
        }
        else {
          uStack_2005c = 0x30017;
        }
      }
      else if (uVar3 == 0x7374) {
        uStack_2005c = 0x30011;
      }
      else if (uVar3 < 0x7375) {
        if (uVar3 == 0x7370) {
          uStack_2005c = 0x3001d;
        }
        else if (uVar3 == 0x7373) {
          uStack_2005c = 0x30014;
        }
        else {
          if (uVar3 != 0x7369) goto LAB_20015cdc;
          uStack_2005c = 0x10015;
        }
      }
      else if (uVar3 == 0x746c) {
        uStack_2005c = 0x300e1;
      }
      else if (uVar3 < 0x746d) {
        if (uVar3 != 0x7377) goto LAB_20015cdc;
        uStack_2005c = 0x3001e;
      }
      else if (uVar3 == 0x746f) {
        uStack_2005c = 0x3001c;
      }
      else {
        if (uVar3 != 0x7470) goto LAB_20015cdc;
        uStack_2005c = 0x300e0;
      }
    }
    else if (uVar3 == 0x7a62) {
      uStack_2005c = 0x300f9;
    }
    else if (uVar3 < 0x7a63) {
      if (uVar3 == 0x7570) {
        uStack_2005c = 0x30030;
      }
      else if (uVar3 < 0x7571) {
        if (uVar3 == 0x756c) {
          uStack_2005c = 0x30037;
        }
        else if (uVar3 == 0x756d) {
          uStack_2005c = 0x30036;
        }
        else {
          if (uVar3 != 0x7566) goto LAB_20015cdc;
          uStack_2005c = 0x30033;
        }
      }
      else if (uVar3 == 0x7573) {
        uStack_2005c = 0x30034;
      }
      else {
        if (uVar3 < 0x7574) {
          if (uVar3 == 0x7571) {
            uStack_2005c = 0x30032;
            goto LAB_200162c8;
          }
        }
        else if ((uVar3 == 0x7672) || (uVar3 == 0x7677)) goto LAB_200162b4;
LAB_20015cdc:
        if (g_protocol_5 == 0) goto LAB_20015e08;
        if (uVar3 == 0x5064) {
          uStack_2005c = 0x300bb;
        }
        else if (uVar3 < 0x5065) {
          if (uVar3 == 0x4665) {
            uStack_2005c = 0x300a2;
          }
          else if (uVar3 < 0x4666) {
            if (uVar3 == 0x4663) {
              uStack_2005c = 0x300a0;
            }
            else if (uVar3 == 0x4664) {
              uStack_2005c = 0x300a3;
            }
            else {
LAB_20015e08:
              if (g_protocol_2 == 0 && g_protocol_5 == 0) goto switchD_20015ec8_caseD_6c64;
              if (uVar3 == 0x6c73) {
                uStack_2005c = 0x30055;
                goto LAB_200162c8;
              }
              if (g_protocol_7 == 0) {
                if (true) {
                  switch(uVar3) {
                  case 0x6c63:
                    uStack_2005c = 0x30057;
                    break;
                  default:
                    goto switchD_20015ec8_caseD_6c64;
                  case 0x6c68:
                    uStack_2005c = 0x30059;
                    break;
                  case 0x6c70:
                    uStack_2005c = 0x30058;
                    break;
                  case 0x6c72:
                    uStack_2005c = 0x30056;
                    break;
                  case 0x6c74:
                    uStack_2005c = 0x3005a;
                  }
                  goto LAB_200162c8;
                }
switchD_20015ec8_caseD_6c64:
                if ((g_protocol_5 == 0 && g_protocol_1 == 0) && g_protocol_4 == 0)
                goto switchD_20015f98_caseD_7065;
                if ((g_protocol_4 != 0) && (uVar3 == 0x7062)) {
                  uStack_2005c = 0x300be;
                  goto LAB_200162c8;
                }
                if (true) {
                  switch(uVar3) {
                  case 0x7063:
                    uStack_2005c = 0x3005b;
                    break;
                  case 0x7064:
                    uStack_2005c = 0x30051;
                    break;
                  default:
                    goto switchD_20015f98_caseD_7065;
                  case 0x706c:
                    uStack_2005c = 0x30053;
                    break;
                  case 0x7072:
                    uStack_2005c = 0x30052;
                    break;
                  case 0x7073:
                    uStack_2005c = 0x30050;
                    break;
                  case 0x7078:
                    uStack_2005c = 0x30054;
                  }
                }
                else {
switchD_20015f98_caseD_7065:
                  if (((g_protocol_5 != 0 || g_protocol_1 != 0) || g_protocol_4 != 0) ||
                      g_protocol_2 != 0) {
                    if (uVar3 == 0x6d35) {
                      uStack_2005c = 0x30065;
                    }
                    else if (uVar3 < 0x6d36) {
                      if (uVar3 == 0x6477) {
                        uStack_2005c = 0x30087;
                      }
                      else if (uVar3 < 0x6478) {
                        if (uVar3 == 0x636c) {
                          uStack_2005c = 0x30072;
                        }
                        else if (uVar3 < 0x636d) {
                          if (uVar3 == 0x6364) {
                            uStack_2005c = 0x30071;
                          }
                          else {
LAB_20016234:
                            if (uVar3 == 0x6467) {
                              uStack_2005c = 0x30082;
                            }
                            else if (uVar3 < 0x6468) {
                              if (uVar3 == 0x6461) {
                                uStack_2005c = 0x30085;
                              }
                              else if (uVar3 == 0x6466) {
                                uStack_2005c = 0x30083;
                              }
                              else {
LAB_200162b4:
                                uStack_2005c = 0;
                              }
                            }
                            else if (uVar3 == 0x726c) {
                              uStack_2005c = 0x30047;
                            }
                            else {
                              if (uVar3 == 0x7a61) goto LAB_200162c0;
                              if (uVar3 != 0x6472) goto LAB_200162b4;
                              uStack_2005c = 0x30084;
                            }
                          }
                        }
                        else if (uVar3 == 0x646c) {
                          uStack_2005c = 0x30081;
                        }
                        else {
                          if (uVar3 != 0x6470) goto LAB_20016234;
                          uStack_2005c = 0x30086;
                        }
                      }
                      else if (uVar3 == 0x6d32) {
                        uStack_2005c = 0x30062;
                      }
                      else if (uVar3 < 0x6d33) {
                        if (uVar3 == 0x6d30) {
                          uStack_2005c = 0x30060;
                        }
                        else {
                          if (uVar3 != 0x6d31) goto LAB_20016234;
                          uStack_2005c = 0x30061;
                        }
                      }
                      else if (uVar3 == 0x6d33) {
                        uStack_2005c = 0x30063;
                      }
                      else {
                        if (uVar3 != 0x6d34) goto LAB_20016234;
                        uStack_2005c = 0x30064;
                      }
                    }
                    else if (uVar3 == 0x6d41) {
                      uStack_2005c = 0x3006a;
                    }
                    else if (uVar3 < 0x6d42) {
                      if (uVar3 == 0x6d37) {
                        uStack_2005c = 0x30067;
                      }
                      else if (uVar3 < 0x6d37) {
                        uStack_2005c = 0x30066;
                      }
                      else if (uVar3 == 0x6d38) {
                        uStack_2005c = 0x30068;
                      }
                      else {
                        if (uVar3 != 0x6d39) goto LAB_20016234;
                        uStack_2005c = 0x30069;
                      }
                    }
                    else if (uVar3 == 0x6d44) {
                      uStack_2005c = 0x3006d;
                    }
                    else if (uVar3 < 0x6d45) {
                      if (uVar3 == 0x6d42) {
                        uStack_2005c = 0x3006b;
                      }
                      else {
                        if (uVar3 != 0x6d43) goto LAB_20016234;
                        uStack_2005c = 0x3006c;
                      }
                    }
                    else if (uVar3 == 0x6d45) {
                      uStack_2005c = 0x3006e;
                    }
                    else {
                      if (uVar3 != 0x6d46) goto LAB_20016234;
                      uStack_2005c = 0x3006f;
                    }
                  }
                }
              }
              else if (uVar3 == 0x7263) {
                uStack_2005c = 0x300d1;
              }
              else if (uVar3 < 0x7264) {
                if (uVar3 == 0x6c64) {
                  uStack_2005c = 0x300d4;
                }
                else {
                  if (uVar3 != 0x7261) goto switchD_20015ec8_caseD_6c64;
                  uStack_2005c = 0x300d3;
                }
              }
              else {
                if (uVar3 == 0x7563) {
                  uStack_2005c = 0x300d0;
                  goto LAB_200162c8;
                }
                if (uVar3 != 0x7a64) {
                  if (uVar3 != 0x726c) goto switchD_20015ec8_caseD_6c64;
                  uStack_2005c = 0x300d2;
                  goto LAB_200162c8;
                }
LAB_200162c0:
                uStack_2005c = 0x300f1;
              }
            }
          }
          else if (uVar3 == 0x467a) {
            uStack_2005c = 0x300a4;
          }
          else {
            if (uVar3 != 0x5063) goto LAB_20015e08;
            uStack_2005c = 0x300ba;
          }
        }
        else if (uVar3 == 0x547a) {
          uStack_2005c = 0x300b2;
        }
        else if (uVar3 < 0x547b) {
          if (uVar3 == 0x5461) {
            uStack_2005c = 0x300b0;
          }
          else {
            if (uVar3 != 0x5464) goto LAB_20015e08;
            uStack_2005c = 0x300b1;
          }
        }
        else if (uVar3 == 0x6663) {
          uStack_2005c = 0x300a1;
        }
        else if (uVar3 == 0x667a) {
          uStack_2005c = 0x300a9;
        }
        else {
          if (uVar3 != 0x6661) goto LAB_20015e08;
          uStack_2005c = 0x300a5;
        }
      }
    }
    else if (uVar3 == 0x7a70) {
      uStack_2005c = 0x300f2;
    }
    else if (uVar3 < 0x7a71) {
      if (uVar3 == 0x7a6d) {
        uStack_2005c = 0x300f4;
      }
      else if (uVar3 == 0x7a6f) {
        uStack_2005c = 0x300f3;
      }
      else {
        if (uVar3 != 0x7a6c) goto LAB_20015cdc;
        uStack_2005c = 0x200fd;
      }
    }
    else if (uVar3 == 0x7a78) {
      uStack_2005c = 0x300fa;
    }
    else if (uVar3 < 0x7a79) {
      if (uVar3 != 0x7a72) goto LAB_20015cdc;
      uStack_2005c = 0x300f0;
    }
    else if (uVar3 == 0x7a79) {
      uStack_2005c = 0x300fb;
    }
    else {
      if (uVar3 != 0x7a7a) goto LAB_20015cdc;
      uStack_2005c = 0x300f8;
    }
LAB_200162c8:
    uVar21 = g_dwCfgFxSlowdown;
    if (uStack_2005c == 0) {
      pbVar17 = pbVar6 + 1;
      uVar35 = (ulonglong)uVar8;
      goto switchD_2001632c_caseD_1e;
    }
    if (uVar8 == 0x20) {
      do {
        pbVar6 = pbVar6 + 1;
      } while (*pbVar6 == 0x20);
    }
    uVar22 = (uint)param_1[2] & uStack_2005c >> 0x10;
    if (uVar22 == 0) {
      cmd_flags = cmd_flags | 4;
      return param_1;
    }
    pbVar29 = pbVar6 + 3;
    pbVar17 = pbVar29;
    if (0xed < (uStack_2005c & 0xffff) - 0x10) {
switchD_2001632c_caseD_14:
      cmd_flags = cmd_flags | 4;
      uVar35 = CONCAT44(uVar22,param_1);
      goto switchD_2001632c_caseD_1e;
    }
    pbVar12 = param_1;
    uVar35 = CONCAT44(uVar22,param_1);
    switch(uStack_2005c & 0xffff) {
    case 0x10:
                    /* WARNING: Could not inline here */
      memcmp((char *)pbVar29,&DAT_20031898,0xc);
      uVar21 = g_dwCfgFxSlowdown;
      if (pbVar29 == (byte *)0x0) {
        if (pbVar6[0x10] - 0x31 < 8) {
          if (pbVar6[0x12] - 0x41 < 0x10) {
            DAT_200815dc = pbVar6[0x10] - 0x30;
            DAT_200815dd = pbVar6[0x12] - 0x40;
            DAT_2007241c = 1;
            g_dwFfpReplyEnabled = 1;
            goto LAB_20019bf4;
          }
          cmd_flags = cmd_flags | 2;
          uVar35 = 0;
        }
        else {
          cmd_flags = cmd_flags | 2;
          uVar35 = 0;
        }
      }
      else {
LAB_20019bf4:
        pbVar17 = pbVar6 + 0x13;
        uVar35 = ZEXT48(pbVar29);
      }
      break;
    case 0x11:
      pbVar17 = cmd_st_handler(pbVar29);
      uVar35 = ZEXT48(pbVar17);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x12:
      pbVar17 = cmd_sd_set_date(pbVar29);
      uVar35 = ZEXT48(pbVar17);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x13:
      uVar22 = parse_digits(pbVar29,3);
      uVar35 = (ulonglong)uVar22;
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else if (uVar22 < 0x65) {
        pbVar17 = pbVar6 + 6;
        DAT_200722a0 = uVar22;
      }
      else {
        cmd_flags = cmd_flags | 2;
      }
      break;
    default:
      goto switchD_2001632c_caseD_14;
    case 0x15:
      uVar22 = parse_digits(pbVar29,4);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else {
        DAT_200722ac = DAT_200722ac | 1;
        pbVar17 = pbVar6 + 7;
        uVar35 = (ulonglong)uVar22;
        DAT_200318ec = uVar22;
        DAT_200c67bc = uVar22;
      }
      break;
    case 0x17:
      uVar22 = parse_mode(pbVar29);
      g_bCfgDefSeqEffect = (undefined1)uVar22;
      pbVar17 = pbVar6 + 5;
      uVar35 = (ulonglong)uVar22;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x18:
      g_dwCfgCarryPageContent = (uint)(*pbVar29 == 0x59);
      pbVar17 = pbVar6 + 4;
      uVar35 = CONCAT44(uVar22,param_1);
      break;
    case 0x19:
      g_dwCfgSuccession = (uint)(*pbVar29 == 0x59);
      pbVar17 = pbVar6 + 4;
      uVar35 = CONCAT44(uVar22,param_1);
      break;
    case 0x1a:
      g_dwCfgArabicAutoDetect = (uint)(*pbVar29 == 0x59);
      pbVar17 = pbVar6 + 4;
      uVar35 = CONCAT44(uVar22,param_1);
      break;
    case 0x1c:
      pbVar17 = pbVar6 + 4;
      uVar35 = CONCAT44(uVar22,param_1);
      if (*pbVar29 - 0x31 < 4) {
        switch(*pbVar29) {
        case 0x31:
          g_dwCfgScrollIfTooWide = 1;
          g_dwCfgTruncateOnChar = 0;
          g_dwCfgTruncateOnWord = 0;
          uVar35 = CONCAT44(uVar22,param_1);
          break;
        case 0x32:
          g_dwCfgScrollIfTooWide = 0;
          g_dwCfgTruncateOnChar = 1;
          g_dwCfgTruncateOnWord = 0;
          uVar35 = ZEXT48(param_1);
          break;
        case 0x33:
          g_dwCfgScrollIfTooWide = 0;
          g_dwCfgTruncateOnChar = 0;
          g_dwCfgTruncateOnWord = 1;
          uVar35 = CONCAT44(uVar22,param_1);
          break;
        case 0x34:
          pbVar6 = DAT_200815e4 + 1;
          *DAT_200815e4 = 0x3a;
          if (g_dwCfgScrollIfTooWide == 0) {
            if (g_dwCfgTruncateOnChar == 0) {
              pbVar30 = pbVar6;
              if (g_dwCfgTruncateOnWord != 0) {
                *pbVar6 = 0x74;
                DAT_200815e4[2] = 0x77;
                pbVar30 = DAT_200815e4 + 3;
              }
            }
            else {
              *pbVar6 = 0x74;
              DAT_200815e4[2] = 99;
              pbVar30 = DAT_200815e4 + 3;
            }
          }
          else {
            DAT_200815e4[1] = 0x73;
            DAT_200815e4[2] = 99;
            pbVar30 = DAT_200815e4 + 3;
          }
          DAT_200815e4 = pbVar30;
          *DAT_200815e4 = 0;
          uVar35 = CONCAT44(pbVar6,&DAT_200815e4);
          uVar21 = g_dwCfgFxSlowdown;
        }
      }
      break;
    case 0x1d:
      uStack_20058 = parse_decimal_packed((int)pbVar29);
      pbVar17 = pbVar29 + (uStack_20058 & 0xf);
      uStack_20058 = uStack_20058 >> 4;
      uVar35 = (ulonglong)uStack_20058;
      uVar21 = g_dwCfgFxSlowdown;
      if ((uStack_20058 != 0xffffffff) && (uVar35 = (ulonglong)uStack_20058, uStack_20058 < 0x65)) {
        piVar27 = (int *)(&DAT_2053f4a8 + uStack_20058 * 0xfc);
        uVar35 = (ulonglong)uStack_20058;
        if ((&g_dwPageRecAllocated)[uStack_20058 * 0x3f] != 0) {
          iVar19 = *(int *)(&DAT_2053f598 + uStack_20058 * 0xfc);
          iVar33 = iVar19 * 0x1d8;
          iVar7 = parse_digits((byte *)&DAT_2053f2d8,2);
          if (iVar7 == 0) {
            iStack_20050 = (&DAT_200a7aac)[iVar19 * 0x76];
          }
          else {
            iStack_20050 = parse_digits((byte *)&DAT_2053f2d8,2);
          }
          local_28 = 0;
          iVar7 = *(int *)(&DAT_200a7aa4 + iVar33);
          (&g_dwPageRecDwellPrimary)[uStack_20058 * 0x3f] = iStack_20050 * iVar7;
          (&g_dwPageRecDwellMirror)[uStack_20058 * 0x3f] = iStack_20050 * iVar7;
          uVar22 = 1;
          do {
            puVar25 = (undefined *)(uVar22 * 4);
            uVar21 = uVar22;
            if ((((uint)piVar27[uVar22 + 0x1b] < 0xc80) &&
                (iVar7 = piVar27[uVar22 + 0x1b] * 0x58c, *(int *)(&DAT_200e97e4 + iVar7) == *piVar27
                )) && (*(int *)(&DAT_200e97ec + iVar7) != 0)) {
              uVar21 = *(uint *)(&DAT_200e9b58 + iVar7);
              if (uVar21 < *(uint *)(&DAT_200a7aa4 + iVar33)) {
                iVar7 = (&g_dwPageRecDwellPrimary)[uStack_20058 * 0x3f] - uVar21 * iStack_20050;
                uVar16 = uVar21;
                while (iVar7 = iVar7 + -1, iVar7 != -1) {
                  uVar16 = uVar16 - 1;
                  if (uVar22 <= (uint)(&DAT_200a7a68)[iVar19 * 0x76 + uVar22 + 0x12]) {
                    piVar23 = piVar27 + uVar22 + 0x1b;
                    uVar8 = uVar22;
                    do {
                      if (uVar16 < *(uint *)(&DAT_200e9b58 + *piVar23 * 0x58c)) {
                        iVar1 = (*piVar23 * 0x163 + uVar16) * 4;
                        *(int *)(&DAT_200e98d0 + iVar1) = *(int *)(&DAT_200e98d0 + iVar1) + 1;
                      }
                      if (1 < uVar21) {
                        *(undefined4 *)
                         (&DAT_200e9b00 +
                         (*piVar23 * 0x163 + *(int *)(&DAT_200e9b58 + *piVar23 * 0x58c)) * 4) = 1;
                      }
                      puVar25 = &DAT_200e97e4;
                      uVar8 = uVar8 + 1;
                      piVar23 = piVar23 + 1;
                    } while (uVar8 <= (uint)(&DAT_200a7a68)[iVar19 * 0x76 + uVar22 + 0x12]);
                  }
                  local_28 = uVar22;
                  if (uVar16 == 0) {
                    uVar16 = *(uint *)(&DAT_200e9b58 + piVar27[uVar22 + 0x1b] * 0x58c);
                  }
                }
                uVar21 = (&DAT_200a7a68)[iVar19 * 0x76 + uVar22 + 0x12];
              }
              else {
                piVar23 = piVar27 + uVar22 + 0x1b;
                uVar16 = uVar22;
                do {
                  if (1 < *(uint *)(&DAT_200a7aa4 + iVar33)) {
                    puVar25 = &DAT_200e97e4;
                    *(undefined4 *)
                     (&DAT_200e9b00 +
                     (*piVar23 * 0x163 + *(int *)(&DAT_200e9b58 + *piVar23 * 0x58c)) * 4) = 1;
                  }
                  uVar16 = uVar16 + 1;
                  uVar21 = (&DAT_200a7a68)[iVar19 * 0x76 + uVar22 + 0x12];
                  piVar23 = piVar23 + 1;
                } while (uVar16 <= uVar21);
              }
            }
            uVar22 = uVar21 + 1;
            uVar35 = ZEXT48(puVar25);
            uVar21 = g_dwCfgFxSlowdown;
          } while (uVar22 < 0x20);
        }
      }
      break;
    case 0x1e:
    case 0x85:
    case 0xd3:
      break;
    case 0x20:
      pbVar30 = pbVar29;
      do {
        uVar22 = hex_to_bin(pbVar30);
        if (uVar22 == 0xffffffff) {
          cmd_flags = cmd_flags | 8;
          uVar35 = 0xffffffff;
          uVar21 = g_dwCfgFxSlowdown;
          goto switchD_2001632c_caseD_1e;
        }
        pbVar30 = pbVar30 + 1;
      } while (pbVar30 != pbVar6 + 0xf);
      iVar33 = 0xc;
      pbVar17 = &DAT_20031898;
      do {
        puVar9 = (undefined4 *)((uint)*pbVar17 - (uint)*pbVar29);
        if (puVar9 != (undefined4 *)0x0) break;
        iVar33 = iVar33 + -1;
        pbVar17 = pbVar17 + 1;
        pbVar29 = pbVar29 + 1;
      } while (iVar33 != 0);
      if (puVar9 == (undefined4 *)0x0) {
        puVar9 = &DAT_200815e4;
        *DAT_200815e4 = 0x3a;
        DAT_200815e4[1] = DAT_200815dc + 0x30;
        DAT_200815e4[2] = 0x2c;
        DAT_200815e4[3] = DAT_200815dd + 0x40;
        pbVar17 = DAT_200815e4 + 4;
        DAT_200815e4 = DAT_200815e4 + 4;
        *pbVar17 = 0;
        g_dwFfpReplyEnabled = 1;
      }
      pbVar17 = pbVar6 + 0xf;
      uVar35 = ZEXT48(puVar9);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x21:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      bin_to_hex((int)pbVar6,2,(uint)DAT_20031400._3_1_);
      DAT_200815e4 = pbVar6;
      bin_to_hex((int)pbVar6,2,(uint)DAT_20031400._2_1_);
      DAT_200815e4 = pbVar6;
      bin_to_hex((int)pbVar6,2,(uint)DAT_20031400._1_1_);
      DAT_200815e4 = pbVar6;
      *pbVar6 = 0;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x22:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      bin_to_hex((int)pbVar6,1,(uint)g_rtc_day_of_week);
      DAT_200815e4 = pbVar6;
      bin_to_hex((int)pbVar6,2,(uint)g_rtc_day_of_month);
      DAT_200815e4 = pbVar6;
      bin_to_hex((int)pbVar6,2,(uint)g_rtc_month);
      DAT_200815e4 = pbVar6;
      bin_to_hex((int)pbVar6,2,(uint)g_rtc_year);
      DAT_200815e4 = pbVar6;
      *pbVar6 = 0;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x23:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      DAT_200815e4 = (byte *)utoa((int)pbVar6,3,DAT_200318b4);
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x24:
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0x3a;
      pbVar6 = DAT_200815e4 + 1;
      DAT_200815e4 = DAT_200815e4 + 1;
      *pbVar6 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x25:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      if (DAT_200318ec < 10000) {
        pbVar6 = (byte *)utoa((int)pbVar6,4,DAT_200318ec);
      }
      else {
        strcpy((char *)pbVar6,"----");
      }
      DAT_200815e4 = pbVar6;
      *pbVar6 = 0;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x28:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      strcpy((char *)pbVar6,&DAT_20031898);
      DAT_200815e4 = pbVar6;
      *pbVar6 = 0;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x29:
      dVar11 = get_app_version();
      if (g_protocol_7 == 0) {
        pbVar6 = DAT_200815e4 + 1;
        *DAT_200815e4 = 0x3a;
        DAT_200815e4 = pbVar6;
        bin_to_hex((int)pbVar6,4,dVar11 >> 0x10);
        DAT_200815e4 = pbVar6 + 1;
        *pbVar6 = 0x2c;
        bin_to_hex((int)DAT_200815e4,4,dVar11 & 0xffff);
        uVar35 = ZEXT48(DAT_200815e4);
        *DAT_200815e4 = 0;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        pbVar6 = DAT_200815e4 + 1;
        *DAT_200815e4 = 0x3a;
        DAT_200815e4 = pbVar6;
        bin_to_hex((int)pbVar6,3,dVar11 >> 0x10);
        DAT_200815e4 = pbVar6 + 1;
        *pbVar6 = 0x2c;
        bin_to_hex((int)DAT_200815e4,2,dVar11 & 0xffff);
        uVar35 = ZEXT48(DAT_200815e4);
        *DAT_200815e4 = 0;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0x2a:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      pcVar10 = utoa((int)pbVar6,4,g_dwCfgPixels);
      DAT_200815e4 = (byte *)(pcVar10 + 1);
      *pcVar10 = ',';
      if (g_dwCfgDoublesided == 0) {
        DAT_200815e4 = (byte *)utoa((int)DAT_200815e4,4,g_dwCfgTotalWidthDlmx * g_dwCfgRowsPerLine);
      }
      else {
        DAT_200815e4 = (byte *)utoa((int)DAT_200815e4,4,
                                    (uint)(g_dwCfgTotalWidthDlmx * g_dwCfgRowsPerLine) >> 1);
      }
      uVar35 = CONCAT44(DAT_200815e4,&DAT_200815e4);
      *DAT_200815e4 = ',';
      if (g_dwCfgColours < 2) {
        DAT_200815e4[1] = 'M';
      }
      else {
        DAT_200815e4[1] = 'C';
      }
      DAT_200815e4 = DAT_200815e4 + 2;
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x2b:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      uVar22 = read_dip_switches();
      bin_to_hex((int)pbVar6,2,uVar22 & 0xff);
      DAT_200815e4 = pbVar6;
      *pbVar6 = 0;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x2c:
      uVar22 = cmd_qe_rl_handler();
      uVar35 = (ulonglong)uVar22;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x2d:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      bin_to_hex((int)pbVar6,2,DAT_20072364);
      DAT_200815e4 = pbVar6;
      *pbVar6 = 0;
      DAT_20072364 = 0;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x2e:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      bin_to_hex((int)pbVar6,2,DAT_20072360);
      DAT_200815e4 = pbVar6;
      *pbVar6 = 0;
      DAT_20072360 = 0;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x2f:
      DAT_200318c0 = 0;
      DAT_2007235c = 0;
      if ((g_protocol_7 != 0) && ((uVar16 & 1) != 0)) {
        uVar16 = uVar16 | 0x40;
      }
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      bin_to_hex((int)pbVar6,2,uVar16);
      DAT_200815e4 = pbVar6;
      *pbVar6 = 0;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x30:
      uVar22 = parse_digits(pbVar29,2);
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        g_dwCfgTimeout = uVar22;
        uVar22 = FUN_2000441c();
        pbVar17 = pbVar6 + 5;
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0x32:
      uVar22 = parse_digits(pbVar29,2);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else if (uVar22 - 1 < 0x14) {
        uVar22 = uVar22 * 1000;
        if (uVar22 < DAT_20072370) {
          DAT_20072370 = uVar22;
        }
        puVar25 = &DAT_2053f4a8;
        iVar33 = 0;
        g_dwCfgSequenceMs = uVar22;
        do {
          if (*(int *)(puVar25 + 4) != 0) {
            puVar13 = &DAT_2053f4a8 + iVar33 * 0xfc;
            iVar7 = 0;
            do {
              if (*(int *)(&DAT_200e97f0 + *(int *)(puVar13 + 0x6c) * 0x58c) != 0) {
                uVar22 = 0;
                do {
                  if ((&DAT_200e9b94)[*(int *)(puVar13 + 0x6c) * 0x58c + uVar22] == 'q') {
                    *(uint *)(&DAT_200e98d0 + (*(int *)(puVar13 + 0x6c) * 0x163 + uVar22) * 4) =
                         g_dwCfgSequenceMs / 1000;
                  }
                  uVar22 = uVar22 + 1;
                } while (uVar22 != 0x14);
              }
              iVar7 = iVar7 + 1;
              puVar13 = puVar13 + 4;
            } while (iVar7 != 0x20);
          }
          iVar33 = iVar33 + 1;
          puVar25 = puVar25 + 0xfc;
        } while (iVar33 != 100);
        pbVar17 = pbVar6 + 5;
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      break;
    case 0x33:
      if (g_protocol_7 == 0) {
        uVar22 = parse_digits(pbVar29,3);
        if (uVar22 == 0xffffffff) {
          cmd_flags = cmd_flags | 2;
          uVar35 = 0xffffffff;
          uVar21 = g_dwCfgFxSlowdown;
        }
        else {
          uVar16 = parse_digits(pbVar6 + 7,3);
          uVar21 = g_dwCfgFxSlowdown;
          if (uVar16 == 0xffffffff) {
            cmd_flags = cmd_flags | 2;
            uVar35 = 0xffffffff;
          }
          else {
            if (pbVar6[6] == 0x2c) goto LAB_2001a1a4;
            cmd_flags = cmd_flags | 8;
            uVar35 = (ulonglong)uVar16;
          }
        }
      }
      else {
        uVar22 = parse_digits(pbVar29,4);
        if (uVar22 == 0xffffffff) {
          cmd_flags = cmd_flags | 2;
          uVar35 = 0xffffffff;
          uVar21 = g_dwCfgFxSlowdown;
        }
        else {
          uVar16 = parse_digits(pbVar6 + 8,4);
          uVar21 = g_dwCfgFxSlowdown;
          if (uVar16 == 0xffffffff) {
            cmd_flags = cmd_flags | 2;
            uVar35 = 0xffffffff;
          }
          else if (pbVar6[7] == 0x2c) {
LAB_2001a1a4:
            if (uVar22 == 999) {
              uVar22 = 1000;
            }
            if (uVar16 == 999) {
              uVar16 = 1000;
            }
            g_dwCfgFlashSpeedA = uVar22 / 10;
            g_dwCfgFlashSpeedB = uVar16 / 10;
            if (g_dwCfgFlashSpeedA < 10) {
              g_dwCfgFlashSpeedA = 10;
            }
            if (g_dwCfgFlashSpeedB < 10) {
              g_dwCfgFlashSpeedB = 10;
            }
            pbVar17 = pbVar6 + 10;
            uVar35 = (ulonglong)uVar16;
            uVar21 = g_dwCfgFxSlowdown;
          }
          else {
            cmd_flags = cmd_flags | 8;
            uVar35 = (ulonglong)uVar16;
          }
        }
      }
      break;
    case 0x34:
      uVar22 = parse_digits(pbVar29,1);
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        DAT_20031904 = uVar22;
        if (8 < uVar22) {
          DAT_20031904 = 9;
        }
        DAT_200722ac = DAT_200722ac | 1;
        if (DAT_200318b4 < g_dwCfgMinBrightness) {
          DAT_200318b4 = g_dwCfgMinBrightness;
        }
        if (g_dwCfgMaxBrightness < DAT_200318b4) {
          DAT_200318b4 = g_dwCfgMaxBrightness;
        }
        switch(DAT_20031904) {
        case 0:
          g_bright_clock_ctrl = 0x460;
          g_dwCfgFxSlowdown = 1;
          break;
        case 1:
          g_bright_clock_ctrl = 0x424;
          g_dwCfgFxSlowdown = 1;
          break;
        case 2:
          g_bright_clock_ctrl = 1000;
          g_dwCfgFxSlowdown = 1;
          break;
        case 3:
          g_bright_clock_ctrl = 0x3a7;
          g_dwCfgFxSlowdown = 1;
          break;
        case 4:
          g_bright_clock_ctrl = 0x460;
          g_dwCfgFxSlowdown = 0;
          break;
        case 5:
          g_bright_clock_ctrl = 0x424;
          g_dwCfgFxSlowdown = 0;
          break;
        case 6:
          g_bright_clock_ctrl = 1000;
          g_dwCfgFxSlowdown = 0;
          break;
        case 7:
          g_bright_clock_ctrl = 0x3a7;
          g_dwCfgFxSlowdown = 0;
          break;
        case 8:
          g_bright_clock_ctrl = 0x36b;
          g_dwCfgFxSlowdown = 0;
          break;
        case 9:
          g_bright_clock_ctrl = 0x32c;
          g_dwCfgFxSlowdown = 0;
        }
        DAT_200c67d8 = DAT_20031904;
        ISR_drive_setup(uVar22,&DAT_200318b4);
        uVar22 = FUN_20000680(DAT_200318b4 * ((((int)g_bright_clock_ctrl / 100) * 0xa0) / 100) >> 3)
        ;
        pbVar17 = pbVar6 + 4;
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0x35:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      DAT_200815e4 = (byte *)utoa((int)pbVar6,2,DAT_20031904);
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x36:
      uVar22 = parse_digits(pbVar29,2);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else if (uVar22 < 0x10) {
        DAT_200722ac = DAT_200722ac | 1;
        pbVar17 = pbVar6 + 5;
        uVar35 = (ulonglong)uVar22;
        g_dwCfgMaintTime = uVar22;
        DAT_200c67c0 = uVar22;
      }
      else {
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      break;
    case 0x37:
      uVar22 = parse_digits(pbVar29,2);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else {
        uVar35 = (ulonglong)uVar22;
        if (uVar22 < 0x3d) {
          pbVar17 = pbVar6 + 5;
          g_dwCfgPinLock = uVar22;
        }
        else {
          cmd_flags = cmd_flags | 2;
        }
      }
      break;
    case 0x38:
      uVar22 = parse_digits(pbVar29,1);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else if (uVar22 < 2) {
        DAT_200722ac = DAT_200722ac | 1;
        pbVar17 = pbVar6 + 4;
        uVar35 = (ulonglong)uVar22;
        DAT_200318f8 = uVar22;
        DAT_200c67c8 = uVar22;
      }
      else {
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      break;
    case 0x40:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      DAT_200815e4 = (byte *)utoa((int)pbVar6,2,g_dwCfgTimeout);
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x41:
      if (DAT_200318d4 == 1) {
        pbVar6 = DAT_200815e4 + 1;
        *DAT_200815e4 = DAT_20090a60;
        if (DAT_20090a60 == 0x30) {
          DAT_200815e4[1] = 0xb0;
          DAT_200815e4[2] = DAT_20090a62;
          DAT_200815e4[3] = DAT_20090a63;
          DAT_200815e4[4] = 0;
          uVar35 = ZEXT48(pbVar6);
          uVar21 = g_dwCfgFxSlowdown;
          DAT_200815e4 = DAT_200815e4 + 5;
        }
        else {
          *pbVar6 = DAT_20090a61;
          if (DAT_20090a62 == 0x5f) {
            DAT_200815e4[2] = 0xb0;
          }
          else {
            DAT_200815e4[2] = DAT_20090a62;
          }
          DAT_200815e4 = DAT_200815e4 + 3;
          uVar5 = CONCAT14(DAT_20090a63,pbVar6);
          if (DAT_20090a63 == 0) {
            *DAT_200815e4 = 0;
            uVar35 = (ulonglong)uVar5;
            uVar21 = g_dwCfgFxSlowdown;
            DAT_200815e4 = pbVar30 + 4;
          }
          else {
            if (DAT_20090a63 == 0x5f) {
              pbVar29 = pbVar30 + 4;
              *DAT_200815e4 = 0xb0;
            }
            else {
              pbVar29 = (byte *)&DAT_200815e4;
              *DAT_200815e4 = DAT_20090a63;
            }
            DAT_200815e4 = pbVar30 + 4;
            puVar9 = (undefined4 *)&DAT_20090a60;
            uVar22 = (uint)DAT_20090a64;
            uVar5 = CONCAT14(DAT_20090a64,pbVar6);
            if (uVar22 == 0) {
              *DAT_200815e4 = DAT_20090a64;
              uVar35 = (ulonglong)uVar5;
              uVar21 = g_dwCfgFxSlowdown;
              DAT_200815e4 = pbVar30 + 5;
            }
            else {
              bVar34 = uVar22 == 0x5f;
              if (bVar34) {
                puVar9 = &DAT_200815e4;
                uVar22 = 0xffffffb0;
                pbVar29 = DAT_200815e4;
              }
              if (bVar34) {
                *pbVar29 = (byte)uVar22;
                *puVar9 = pbVar29 + 1;
              }
              else {
                *DAT_200815e4 = (byte)uVar22;
                DAT_200815e4 = pbVar30 + 5;
              }
              if (DAT_20090a65 == 0) {
                *DAT_200815e4 = 0;
                uVar35 = CONCAT44(uVar22,pbVar6);
                uVar21 = g_dwCfgFxSlowdown;
                DAT_200815e4 = DAT_200815e4 + 1;
              }
              else {
                *DAT_200815e4 = DAT_20090a65;
                DAT_200815e4[1] = 0;
                uVar35 = CONCAT44(DAT_200815e4,&DAT_200815e4);
                uVar21 = g_dwCfgFxSlowdown;
                DAT_200815e4 = DAT_200815e4 + 2;
              }
            }
          }
        }
      }
      else {
        pbVar6 = DAT_200815e4 + 1;
        *DAT_200815e4 = DAT_2008c180;
        if (DAT_2008c180 == 0x30) {
          DAT_200815e4[1] = 0xb0;
          DAT_200815e4[2] = DAT_2008c182;
          DAT_200815e4[3] = DAT_2008c183;
          DAT_200815e4[4] = 0;
          uVar35 = ZEXT48(pbVar6);
          uVar21 = g_dwCfgFxSlowdown;
          DAT_200815e4 = DAT_200815e4 + 5;
        }
        else {
          *pbVar6 = DAT_2008c181;
          if (DAT_2008c182 == 0x5f) {
            DAT_200815e4[2] = 0xb0;
          }
          else {
            DAT_200815e4[2] = DAT_2008c182;
          }
          DAT_200815e4 = DAT_200815e4 + 3;
          uVar5 = CONCAT14(DAT_2008c183,pbVar6);
          if (DAT_2008c183 == 0) {
            *DAT_200815e4 = 0;
            uVar35 = (ulonglong)uVar5;
            uVar21 = g_dwCfgFxSlowdown;
            DAT_200815e4 = pbVar30 + 4;
          }
          else {
            if (DAT_2008c183 == 0x5f) {
              pbVar29 = pbVar30 + 4;
              *DAT_200815e4 = 0xb0;
            }
            else {
              pbVar29 = (byte *)&DAT_200815e4;
              *DAT_200815e4 = DAT_2008c183;
            }
            DAT_200815e4 = pbVar30 + 4;
            puVar9 = (undefined4 *)&DAT_2008c180;
            uVar22 = (uint)DAT_2008c184;
            uVar5 = CONCAT14(DAT_2008c184,pbVar6);
            if (uVar22 == 0) {
              *DAT_200815e4 = DAT_2008c184;
              uVar35 = (ulonglong)uVar5;
              uVar21 = g_dwCfgFxSlowdown;
              DAT_200815e4 = pbVar30 + 5;
            }
            else {
              bVar34 = uVar22 == 0x5f;
              if (bVar34) {
                puVar9 = &DAT_200815e4;
                uVar22 = 0xffffffb0;
                pbVar29 = DAT_200815e4;
              }
              if (bVar34) {
                *pbVar29 = (byte)uVar22;
                *puVar9 = pbVar29 + 1;
              }
              else {
                *DAT_200815e4 = (byte)uVar22;
                DAT_200815e4 = pbVar30 + 5;
              }
              if (DAT_2008c185 == 0) {
                *DAT_200815e4 = 0;
                uVar35 = CONCAT44(uVar22,pbVar6);
                uVar21 = g_dwCfgFxSlowdown;
                DAT_200815e4 = DAT_200815e4 + 1;
              }
              else {
                uVar35 = CONCAT44(DAT_200815e4,&DAT_200815e4);
                *DAT_200815e4 = DAT_2008c185;
                DAT_200815e4[1] = 0;
                DAT_200815e4 = DAT_200815e4 + 2;
                uVar21 = g_dwCfgFxSlowdown;
              }
            }
          }
        }
      }
      break;
    case 0x42:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      DAT_200815e4 = (byte *)utoa((int)pbVar6,2,g_dwCfgSequenceMs / 1000);
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x43:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      if (g_protocol_7 == 0) {
        pcVar10 = utoa((int)pbVar6,3,g_dwCfgFlashSpeedA * 10);
        DAT_200815e4 = (byte *)(pcVar10 + 1);
        *pcVar10 = ',';
        DAT_200815e4 = (byte *)utoa((int)DAT_200815e4,3,g_dwCfgFlashSpeedB * 10);
      }
      else {
        pcVar10 = utoa((int)pbVar6,4,g_dwCfgFlashSpeedA * 10);
        DAT_200815e4 = (byte *)(pcVar10 + 1);
        *pcVar10 = ',';
        DAT_200815e4 = (byte *)utoa((int)DAT_200815e4,4,g_dwCfgFlashSpeedB * 10);
      }
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x46:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      DAT_200815e4 = (byte *)utoa((int)pbVar6,2,g_dwCfgMaintTime);
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x47:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      DAT_200815e4 = (byte *)utoa((int)pbVar6,2,g_dwCfgPinLock);
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x48:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      DAT_200815e4 = (byte *)utoa((int)pbVar6,1,DAT_200318f8);
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x49:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      DAT_200815e4 = (byte *)utoa((int)pbVar6,3,DAT_200722a0);
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x50:
      if (g_dwActivePageIdx != 0xffffffff) {
        FUN_2000f120();
      }
      uVar22 = parse_decimal_packed((int)pbVar29);
      pbVar17 = pbVar29 + (uVar22 & 0xf);
      uVar22 = uVar22 >> 4;
      uVar21 = g_dwCfgFxSlowdown;
      if ((uVar22 == 0xffffffff) || (g_dwCfgDdxFixedLine == uVar22)) {
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      else if (uVar22 < 0x65) {
        g_dwActivePageIdx = uVar22;
        page_slot_set_active(uVar22,0);
        page_slot_release(g_dwActivePageIdx);
        g_dwGeometryInstallActive = 1;
        uVar22 = page_install_geometry
                           (g_dwActivePageIdx,g_dwCfgDdxModalV1,g_dwCfgDdxModalV2,g_dwCfgDdxModalV4,
                            g_dwCfgDdxModalV3);
        g_dwGeometryInstallActive = 0;
        if (uVar22 == 0) {
          *(undefined4 *)(&g_dwPageRecModalActive + g_dwActivePageIdx * 0xfc) = 1;
          uVar35 = 0;
          uVar21 = g_dwCfgFxSlowdown;
        }
        else {
          g_dwCmdErrorCode = uVar22 | uStack_20058 << 0x18;
          cmd_flags = cmd_flags | 2;
          uVar35 = (ulonglong)uVar22;
          uVar21 = g_dwCfgFxSlowdown;
        }
      }
      else {
        g_dwCmdErrorCode = uVar22 << 0x18 | 4;
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      break;
    case 0x51:
      uVar22 = parse_digits(pbVar29,2);
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        g_dwCmdErrorCode = page_slot_set_active(uVar22,0);
        pbVar17 = pbVar6 + 5;
        uVar35 = (ulonglong)g_dwCmdErrorCode;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0x52:
      uVar22 = FUN_200268c0();
      uVar35 = (ulonglong)uVar22;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x53:
      FUN_2000f120();
      iVar33 = 0;
      do {
        *(undefined4 *)((int)&uStack_20038 + iVar33) =
             *(undefined4 *)((int)&g_dwPlaylistQueue + iVar33);
        *(undefined4 *)((int)&g_dwPlaylistQueue + iVar33) = 0xffffffff;
        iVar33 = iVar33 + 4;
      } while (iVar33 != 800);
      uVar22 = 0;
      g_dwPlaylistLength = 0;
      g_dwPlaylistBuildIdx = 0;
      if (*pbVar29 == 0x2a) {
        puVar25 = &DAT_2053f4a8;
        do {
          if ((*(int *)(puVar25 + 0x30) != 0) && (g_dwCfgDdxFixedLine != uVar22)) {
            (&g_dwPlaylistQueue)[g_dwPlaylistBuildIdx] = uVar22;
            g_dwPlaylistBuildIdx = g_dwPlaylistBuildIdx + 1;
            g_dwPlaylistLength = g_dwPlaylistLength + 1;
          }
          uVar22 = uVar22 + 1;
          puVar25 = puVar25 + 0xfc;
        } while (uVar22 != 100);
        pbVar17 = pbVar6 + 4;
        pbVar6 = &UNK_00000064;
      }
      else {
        while( true ) {
          pbVar6 = (byte *)parse_decimal_packed((int)pbVar29);
          iVar33 = (int)pbVar6 >> 4;
          if (iVar33 == -1) {
            g_dwCmdErrorCode = 0xff000003;
            cmd_flags = cmd_flags | 2;
            return pbVar6;
          }
          if ((&g_dwPageRecAllocated)[iVar33 * 0x3f] != 0) {
            (&g_dwPlaylistQueue)[g_dwPlaylistBuildIdx] = iVar33;
            g_dwPlaylistBuildIdx = g_dwPlaylistBuildIdx + 1;
            g_dwPlaylistLength = g_dwPlaylistLength + 1;
          }
          pbVar17 = pbVar29 + ((uint)pbVar6 & 0xf);
          bVar18 = *pbVar17;
          if (bVar18 == 0x21 || bVar18 == 0) break;
          if (bVar18 != 0x2c) {
            cmd_flags = cmd_flags | 8;
            return pbVar6;
          }
          pbVar29 = pbVar17 + 1;
        }
      }
      g_dwPlaylistBuildIdx = 0xffffffff;
      if (g_dwCfgClearOldQueue != 0) {
        iVar33 = 0;
        do {
          pbVar30 = *(byte **)((int)&uStack_20038 + iVar33);
          if (pbVar30 != (byte *)0xffffffff) {
            iVar7 = 0;
            do {
              pbVar6 = pbVar30;
              if (*(byte **)((int)&g_dwPlaylistQueue + iVar7) == pbVar30) goto LAB_20017cdc;
              iVar7 = iVar7 + 4;
            } while (iVar7 != 800);
            if (DAT_200909ac == 0) {
              if ((&g_dwPageRecLoadedProtect)[(int)pbVar30 * 0x3f] == 0) {
                (&g_dwPageRecDeactivateQueued)[(int)pbVar30 * 0x3f] = 1;
                (&g_dwPageRecReadyForRender)[(int)pbVar30 * 0x3f] = 1;
              }
            }
            else {
              pbVar6 = (byte *)page_slot_set_active((uint)pbVar30,0);
            }
          }
LAB_20017cdc:
          iVar33 = iVar33 + 4;
        } while (iVar33 != 800);
      }
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      if ((g_dwCfgCarryPageContent != 0) && (uVar35 = ZEXT48(pbVar6), 1 < g_dwPlaylistLength)) {
        piStack_20040 = &g_dwPlaylistQueue;
        uStack_2003c = 1;
        do {
          iVar7 = *piStack_20040;
          puVar13 = &DAT_2053f4a8 + iVar7 * 0xfc;
          iVar33 = piStack_20040[1];
          puVar25 = &DAT_2053f4a8;
          if ((&g_dwPageRecAllocated)[iVar7 * 0x3f] != 0) {
            iVar19 = iVar33 * 0xfc;
            puVar20 = &DAT_2053f4a8 + iVar19;
            if ((((&g_dwPageRecAllocated)[iVar33 * 0x3f] != 0) &&
                ((&g_dwPageRecTopologyKey)[iVar7 * 0x3f] == (&g_dwPageRecTopologyKey)[iVar33 * 0x3f]
                )) && ((puVar26 = puVar20, g_protocol_3 == 0 ||
                       (puVar25 = puVar20, *(int *)(&DAT_2053f4fc + iVar19) != 0)))) {
              do {
                puVar25 = *(undefined **)(puVar13 + 0x6c);
                if (puVar25 != (undefined *)0xffffffff) {
                  if ((g_protocol_3 != 0) &&
                     (*(int *)(&DAT_200e97ec + *(int *)(puVar26 + 0x6c) * 0x58c) != 0)) break;
                  iVar33 = (int)puVar25 * 0x58c;
                  src = &DAT_200e97e4 + iVar33;
                  if ((*(int *)(&DAT_200e97ec + iVar33) != 0) &&
                     (*(int *)(&DAT_200e97ec + *(int *)(puVar26 + 0x6c) * 0x58c) == 0)) {
                    uVar22 = FUN_20024c9c();
                    *(uint *)(puVar26 + 0x6c) = uVar22;
                    dst = (uint *)(&DAT_200e97e4 + uVar22 * 0x58c);
                    memcpy((undefined1 *)dst,src,0x58c);
                    *(int *)(&DAT_2053f510 + iVar19) = *(int *)(&DAT_2053f510 + iVar19) + 1;
                    if (*(int *)(&DAT_200e9b58 + iVar33) != 0) {
                      uStack_2004c = 0;
                      puVar28 = dst;
                      do {
                        uVar22 = text_slot_alloc();
                        if (uVar22 == 0xffffffff) {
                          g_dwCmdErrorCode = 0xffff0082;
                          cmd_flags = cmd_flags | 8;
                          return (byte *)0xffffffff;
                        }
                        strcpy(&DAT_2055b000 + uVar22 * 0x1000,
                               &DAT_2055b000 + *(int *)(src + 0x2d0) * 0x1000);
                        puVar28[0xb4] = uVar22;
                        *dst = uStack_2003c;
                        uStack_2004c = uStack_2004c + 1;
                        src = src + 4;
                        puVar28 = puVar28 + 1;
                      } while (uStack_2004c < *(uint *)(&DAT_200e9b58 + iVar33));
                    }
                  }
                }
                puVar13 = puVar13 + 4;
                puVar26 = puVar26 + 4;
                puVar25 = puVar20;
              } while (puVar26 != (undefined *)(iVar19 + 0x2053f528));
            }
          }
          uStack_2003c = uStack_2003c + 1;
          piStack_20040 = piStack_20040 + 1;
          uVar35 = CONCAT44(uStack_2003c,puVar25);
          uVar21 = g_dwCfgFxSlowdown;
        } while (uStack_2003c < g_dwPlaylistLength);
      }
      break;
    case 0x54:
      iVar33 = 0;
      do {
        iVar7 = iVar33;
        *(undefined4 *)((int)&g_dwPlaylistQueue + iVar7) = 0xffffffff;
        iVar33 = iVar7 + 4;
      } while (iVar7 + 4 != 400);
      g_dwPlaylistLength = iVar7 - 0x18c;
      g_dwPlaylistBuildIdx = 0xffffffff;
      g_dwPlaylistAuxB = 0xffffffff;
      g_dwPlaylistAuxC = 0xffffffff;
      uVar35 = CONCAT44(0xffffffff,param_1);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x55:
      goto switchD_2001632c_caseD_55;
    case 0x56:
      uVar22 = parse_digits(pbVar29,2);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        g_dwCmdErrorCode = 0x99;
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else if (g_dwActivePageIdx == 0xffffffff) {
        g_dwCmdErrorCode = uVar22 << 0x18 | 0x9a;
        cmd_flags = cmd_flags | 2;
        uVar35 = CONCAT44(g_dwActivePageIdx,uVar22);
      }
      else if ((uVar22 == g_dwActivePageIdx) ||
              (g_dwActivePageIdx == uVar22 + (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode])) {
        if ((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] < uVar22) {
          uVar22 = uVar22 - (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
        }
        uVar22 = g_dwLinePageCommitted[uVar22];
        uVar4 = CONCAT44(g_dwActivePageIdx,uVar22);
        uVar35 = CONCAT44(g_dwActivePageIdx,uVar22);
        if (uVar22 != 0xffffffff) {
          (&g_dwPageRecDeactivateQueued)[uVar22 * 0x3f] = 1;
          *(undefined4 *)(&g_dwPageRecQueuePosition + uVar22 * 0xfc) = 1;
          (&g_dwPageRecReadyForRender)[uVar22 * 0x3f] = 1;
          uVar35 = uVar4;
          uVar21 = g_dwCfgFxSlowdown;
        }
      }
      else {
        g_dwCmdErrorCode = g_dwActivePageIdx << 0x18 | 0x9b | uVar22 << 0x10;
        cmd_flags = cmd_flags | 2;
        uVar35 = CONCAT44(g_dwActivePageIdx,uVar22);
      }
      break;
    case 0x57:
      iStack_20054 = 1;
switchD_2001632c_caseD_55:
      pbVar30 = param_1;
      if (g_dwActivePageIdx != 0xffffffff) {
        pbVar30 = (byte *)page_render_teardown();
      }
      uVar35 = ZEXT48(pbVar30);
      uVar21 = g_dwCfgFxSlowdown;
      if (g_protocol_7 == 0) {
        uVar22 = parse_digits(pbVar29,2);
        uVar21 = g_dwCfgFxSlowdown;
        if (uVar22 == 0xffffffff) {
          cmd_flags = cmd_flags | 2;
          uVar35 = 0xffffffff;
        }
        else if (g_dwCfgDoublesided == 0) {
          if ((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] < uVar22) {
            g_dwCmdErrorCode = uVar22 << 0x18 | 0x91;
            cmd_flags = cmd_flags | 2;
            uVar35 = (ulonglong)uVar22;
          }
          else {
LAB_2001752c:
            if ((uint)(g_dwCfgRowsPerLine * g_dwCfgTotalWidthDlmx) <
                (uint)(&g_dwCfgDlmxY)[(g_dwCfgCurrentMode * 0x3c + uVar22) * 4]) {
              g_dwCmdErrorCode = uVar22 << 0x18 | 0x91;
              cmd_flags = cmd_flags | 2;
              uVar35 = CONCAT44(g_dwCfgRowsPerLine,g_dwCfgCurrentMode);
            }
            else {
              if (g_dwLinePageCommitted[uVar22] == 0xffffffff) {
                g_dwLinePageStaging[uVar22] = 0xffffffff;
                g_dwActivePageIdx = uVar22;
              }
              else {
                g_dwActivePageIdx = g_dwLinePageStaging[uVar22];
                if (g_dwActivePageIdx == 0xffffffff) {
                  g_dwActivePageIdx = uVar22;
                  if (g_dwLinePageCommitted[uVar22] <=
                      (uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode]) {
                    g_dwActivePageIdx = uVar22 + (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
                  }
                }
                else {
                  g_dwLinePageStaging[uVar22] = 0xffffffff;
                }
              }
              if (iStack_20054 == 0) {
                page_slot_set_active(g_dwActivePageIdx,1);
                page_slot_release(g_dwActivePageIdx);
              }
              else {
                page_slot_set_active(g_dwActivePageIdx,0);
                page_slot_set_active(g_dwLinePageCommitted[uVar22],0);
                page_slot_release(g_dwActivePageIdx);
                page_slot_release(g_dwLinePageCommitted[uVar22]);
              }
              iVar33 = g_dwCfgCurrentMode * 0x3c + (uVar22 - 1);
              uVar22 = page_install_geometry
                                 (g_dwActivePageIdx,(&g_dwCfgDlmxX)[iVar33 * 4],
                                  (&g_dwCfgDlmxY)[iVar33 * 4],(&g_dwCfgDlmxW)[iVar33 * 4],
                                  (&g_dwCfgDlmxH)[iVar33 * 4]);
              if (uVar22 == 0) {
                iVar33 = g_dwActivePageIdx * 0xfc;
                *(int *)(&DAT_2053f4b4 + iVar33) = iStack_20054;
                *(undefined4 *)(&g_dwPageRecModalActive + iVar33) = 1;
                iStack_20054 = 0;
                pbVar17 = pbVar6 + 5;
                uVar35 = 0;
                uVar21 = g_dwCfgFxSlowdown;
              }
              else {
                g_dwCmdErrorCode = uVar22 | g_dwActivePageIdx << 0x18;
                cmd_flags = cmd_flags | 2;
                iStack_20054 = 0;
                uVar35 = 0;
                uVar21 = g_dwCfgFxSlowdown;
              }
            }
          }
        }
        else {
          if (uVar22 <= (uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1)
          goto LAB_2001752c;
          g_dwCmdErrorCode = uVar22 << 0x18 | 0x91;
          cmd_flags = cmd_flags | 2;
          uVar35 = (ulonglong)uVar22;
        }
      }
      break;
    case 0x58:
      uVar22 = parse_digits(pbVar29,2);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        g_dwCmdErrorCode = 0x9c;
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else if (g_dwActivePageIdx == 0xffffffff) {
        g_dwCmdErrorCode = 0x9d;
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      else {
        if (uVar22 == 0) {
          uVar22 = 0xffffffff;
        }
        *(uint *)(&g_dwPageRecQueuePosition + g_dwActivePageIdx * 0xfc) = uVar22;
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0x59:
      uVar22 = parse_digits(pbVar29,2);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        g_dwCmdErrorCode = 0x96;
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else {
        uVar35 = CONCAT44(g_dwActivePageIdx,uVar22);
        if (g_dwActivePageIdx == 0xffffffff) {
          g_dwCmdErrorCode = uVar22 << 0x18 | 0x97;
          cmd_flags = cmd_flags | 2;
          uVar35 = CONCAT44(g_dwActivePageIdx,uVar22);
        }
        else if ((uVar22 == g_dwActivePageIdx) ||
                (g_dwActivePageIdx == uVar22 + (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode])) {
          *(undefined4 *)(&g_dwPageRecEnable + g_dwActivePageIdx * 0xfc) = 1;
          uVar21 = g_dwCfgFxSlowdown;
        }
        else {
          g_dwCmdErrorCode = g_dwActivePageIdx << 0x18 | 0x98 | uVar22 << 0x10;
          cmd_flags = cmd_flags | 2;
          uVar35 = CONCAT44(g_dwActivePageIdx,uVar22);
        }
      }
      break;
    case 0x5a:
      uVar22 = page_render_teardown();
      if (*pbVar29 == 0x2a) {
        uVar21 = 0;
        iVar33 = 0;
        do {
          iVar7 = *(int *)((int)g_dwLinePageStaging + iVar33);
          if (iVar7 != -1) {
            *(undefined4 *)(&g_dwPageRecEnable + iVar7 * 0xfc) = 0;
            (&g_dwPageRecScheduleMark)[iVar7 * 0x3f] = 1;
            uVar22 = *(uint *)((int)g_dwLinePageCommitted + iVar33);
            if (uVar22 != 0xffffffff) {
              uVar22 = page_slot_set_active(uVar22,0);
            }
            *(undefined4 *)((int)g_dwLinePageCommitted + iVar33) =
                 *(undefined4 *)((int)g_dwLinePageStaging + iVar33);
            *(undefined4 *)((int)g_dwLinePageStaging + iVar33) = 0xffffffff;
          }
          uVar21 = uVar21 + 1;
          iVar33 = iVar33 + 4;
        } while (uVar21 <= (uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode]);
        pbVar17 = pbVar6 + 5;
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        while( true ) {
          pbVar6 = (byte *)parse_digits(pbVar29,2);
          if (pbVar6 == (byte *)0xffffffff) {
            g_dwCmdErrorCode = 0xff00009e;
            cmd_flags = cmd_flags | 2;
            return (byte *)0xffffffff;
          }
          if (((byte *)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] < pbVar6) ||
             ((g_dwCfgDoublesided != 0 &&
              ((byte *)((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1) < pbVar6)))) {
            g_dwCmdErrorCode = (int)pbVar6 << 0x18 | 0x90;
            cmd_flags = cmd_flags | 2;
            return pbVar6;
          }
          uVar22 = g_dwLinePageStaging[(int)pbVar6];
          pbVar30 = pbVar6;
          if (uVar22 != 0xffffffff) {
            *(undefined4 *)(&g_dwPageRecEnable + uVar22 * 0xfc) = 0;
            (&g_dwPageRecScheduleMark)[uVar22 * 0x3f] = 1;
            pbVar30 = (byte *)g_dwLinePageCommitted[(int)pbVar6];
            if (pbVar30 != (byte *)0xffffffff) {
              pbVar30 = (byte *)page_slot_set_active((uint)pbVar30,0);
            }
            g_dwLinePageCommitted[(int)pbVar6] = g_dwLinePageStaging[(int)pbVar6];
            g_dwLinePageStaging[(int)pbVar6] = 0xffffffff;
          }
          bVar18 = pbVar29[2];
          pbVar17 = pbVar29 + 2;
          uVar35 = ZEXT48(pbVar30);
          uVar21 = g_dwCfgFxSlowdown;
          if (bVar18 == 0x21 || bVar18 == 0) break;
          if (bVar18 != 0x2c) {
            cmd_flags = cmd_flags | 8;
            return pbVar30;
          }
          pbVar29 = pbVar29 + 3;
        }
      }
      break;
    case 0x5b:
      pbVar17 = pbVar6 + 4;
      if (*pbVar29 == 0x79) {
        *(undefined4 *)(&g_dwPageRecCarryYn + g_dwActivePageIdx * 0xfc) = 1;
        uVar35 = CONCAT44(uVar22,param_1);
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        *(undefined4 *)(&g_dwPageRecCarryYn + g_dwActivePageIdx * 0xfc) = 0;
        uVar35 = CONCAT44(uVar22,param_1);
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0x5c:
switchD_2001632c_caseD_5c:
      if (g_dwActivePageIdx != 0xffffffff) {
        FUN_2000f120();
      }
      uVar22 = parse_decimal_packed((int)pbVar29);
      pbVar17 = pbVar29 + (uVar22 & 0xf);
      uVar22 = uVar22 >> 4;
      uVar21 = g_dwCfgFxSlowdown;
      if ((uVar22 == 0xffffffff) || (g_dwCfgDdxFixedLine == uVar22)) {
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      else if (uVar22 < 0x65) {
        g_dwActivePageIdx = uVar22;
        page_slot_set_active(uVar22,0);
        page_slot_release(g_dwActivePageIdx);
        g_dwGeometryInstallActive = 1;
        uVar22 = page_install_geometry
                           (g_dwActivePageIdx,g_dwCfgDdxModalV1,g_dwCfgDdxModalV2,g_dwCfgDdxModalV4,
                            g_dwCfgDdxModalV3);
        g_dwGeometryInstallActive = 0;
        if (uVar22 == 0) {
          iVar33 = g_dwActivePageIdx * 0xfc;
          *(undefined4 *)(&g_dwPageRecModalActive + iVar33) = 1;
          *(undefined4 *)(&g_dwPageRecPxModalFlag + iVar33) = 1;
          if (9 < g_dwPxLoadCounter) {
            g_dwPxLoadCounter = g_dwPxLoadCounter + 1;
          }
          uVar35 = 0;
          uVar21 = g_dwCfgFxSlowdown;
        }
        else {
          g_dwCmdErrorCode = uVar22 | uStack_20058 << 0x18;
          cmd_flags = cmd_flags | 2;
          uVar35 = (ulonglong)uVar22;
          uVar21 = g_dwCfgFxSlowdown;
        }
      }
      else {
        g_dwCmdErrorCode = uVar22 << 0x18 | 4;
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      break;
    case 0x60:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 0;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x61:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 1;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x62:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 2;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 99:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 3;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 100:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 4;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x65:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 5;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x66:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 6;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x67:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 7;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x68:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 8;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x69:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 9;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x6a:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 10;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x6b:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 0xb;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x6c:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 0xc;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x6d:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 0xd;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x6e:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 0xe;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x6f:
      pbVar6 = param_1;
      if (g_protocol_2 != 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          pbVar6 = (byte *)FUN_200268c0();
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar21 = 0;
          do {
            if (((g_dwCfgDdxFixedLine != uVar21) && (uVar22 + g_dwCfgDdxFixedLine != uVar21)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar16 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar16 != uVar21 &&
                 (uVar16 + uVar22 != uVar21)))))) {
              page_slot_set_active(uVar21,0);
              pbVar6 = (byte *)page_slot_release(uVar21);
              g_dwLinePageCommitted[uVar21] = 0xffffffff;
              g_dwLinePageStaging[uVar21] = 0xffffffff;
            }
            uVar21 = uVar21 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          } while (uVar21 <= uVar22 * 2);
        }
      }
      g_dwCfgCurrentMode = 0xf;
      uVar35 = ZEXT48(pbVar6);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0x71:
      uVar35 = CONCAT44(uVar22,param_1);
      if (g_dwSlotSkipBody == 0) {
        if ((g_dwCfgDdxFixedLineSet == 0) || (g_dwCfgDdxFixedYn == 0)) {
          uVar22 = FUN_200268c0();
          uVar35 = (ulonglong)uVar22;
          uVar21 = g_dwCfgFxSlowdown;
        }
        else if (g_protocol_2 == 0) {
          uVar22 = 0;
          pbVar6 = param_1;
          do {
            if (g_dwCfgDdxFixedLine != uVar22) {
              page_slot_set_active(uVar22,0);
              pbVar6 = (byte *)page_slot_release(uVar22);
              (&g_dwPlaylistQueue)[uVar22] = 0xffffffff;
            }
            uVar22 = uVar22 + 1;
            uVar35 = ZEXT48(pbVar6);
            uVar21 = g_dwCfgFxSlowdown;
          } while (uVar22 != 200);
        }
        else {
          uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
          uVar16 = 0;
          pbVar6 = param_1;
          do {
            if (((g_dwCfgDdxFixedLine != uVar16) && (uVar22 + g_dwCfgDdxFixedLine != uVar16)) &&
               ((g_dwCfgDoublesided == 0 ||
                ((uVar21 = g_dwCfgDdxFixedLine + (uVar22 >> 1), uVar21 != uVar16 &&
                 (uVar21 + uVar22 != uVar16)))))) {
              page_slot_set_active(uVar16,0);
              pbVar6 = (byte *)page_slot_release(uVar16);
              g_dwLinePageCommitted[uVar16] = 0xffffffff;
              g_dwLinePageStaging[uVar16] = 0xffffffff;
            }
            uVar16 = uVar16 + 1;
            uVar22 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
            uVar35 = CONCAT44(uVar22,pbVar6);
            uVar21 = g_dwCfgFxSlowdown;
          } while (uVar16 <= uVar22 * 2);
        }
      }
      break;
    case 0x72:
      uVar35 = CONCAT44(uVar22,param_1);
      if (g_dwSlotSkipBody == 0) {
        if (g_protocol_2 == 0) {
          uVar22 = parse_digits(pbVar29,1);
          if (uVar22 == 0xffffffff) {
            cmd_flags = cmd_flags | 2;
            uVar35 = 0xffffffff;
            uVar21 = g_dwCfgFxSlowdown;
          }
          else {
            uVar21 = g_dwPlaylistAuxB;
            if (g_dwPlaylistAuxB != 0xffffffff) {
              uVar21 = line_reset_for_scroll(g_dwPlaylistAuxB,uVar22);
              *(undefined4 *)
               (&DAT_200e97f0 + (&DAT_2053f514)[g_dwPlaylistAuxB * 0x3f + uVar22] * 0x58c) = 0;
            }
            pbVar17 = pbVar6 + 4;
            uVar35 = (ulonglong)uVar21;
            uVar21 = g_dwCfgFxSlowdown;
          }
        }
        else {
          uVar22 = parse_digits(pbVar29,2);
          uVar21 = g_dwCfgFxSlowdown;
          if (uVar22 == 0xffffffff) {
            cmd_flags = cmd_flags | 2;
            uVar35 = 0xffffffff;
          }
          else if ((uVar22 == g_dwCfgDdxFixedLine) ||
                  ((g_dwCfgDoublesided != 0 &&
                   (uVar22 == g_dwCfgDdxFixedLine +
                              ((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1))))) {
            pbVar17 = pbVar6 + 5;
            uVar35 = CONCAT44(g_dwCfgDdxFixedLine,uVar22);
          }
          else {
            uVar21 = g_dwLinePageCommitted[uVar22];
            if (uVar21 != 0xffffffff) {
              uVar21 = page_slot_set_active(uVar21,0);
            }
            if ((g_dwCfgDoublesided != 0) &&
               (uVar21 = g_dwLinePageCommitted
                         [uVar22 + ((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1)],
               uVar21 != 0xffffffff)) {
              uVar21 = page_slot_set_active(uVar21,0);
            }
            pbVar17 = pbVar6 + 5;
            uVar35 = (ulonglong)uVar21;
            uVar21 = g_dwCfgFxSlowdown;
          }
        }
      }
      break;
    case 0x81:
      if (g_protocol_2 == 0) {
        pbVar17 = cmd_dl_handler((char *)pbVar29);
      }
      else {
        pbVar17 = cmd_dl_handler_alt((char *)pbVar29);
      }
      uVar35 = ZEXT48(pbVar17);
      uVar21 = g_dwCfgFxSlowdown;
      if (g_dwCfgDoublesided != 0) {
        uVar22 = parse_decimal_packed((int)pbVar29);
        if (DAT_200723f0 == 0) {
          uVar22 = (uVar22 >> 4) + ((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1);
          if (uVar22 < 10) {
            *pbVar29 = 0x30;
            pcVar10 = utoa((int)(pbVar6 + 4),1,uVar22);
            pbVar30 = (byte *)(pcVar10 + -2);
          }
          else {
            pcVar10 = utoa((int)pbVar29,2,uVar22);
            pbVar30 = (byte *)(pcVar10 + -2);
          }
        }
        else {
          uVar22 = (uVar22 >> 4) + ((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1);
          if (uVar22 < 10) {
            pcVar10 = utoa((int)pbVar29,1,uVar22);
            pbVar30 = (byte *)(pcVar10 + -1);
          }
          else {
            pcVar10 = utoa((int)(pbVar6 + 2),2,uVar22);
            pbVar30 = (byte *)(pcVar10 + -2);
          }
        }
        iVar33 = 6;
        do {
          bVar18 = pbVar30[iVar33];
          if (bVar18 == 0x3e) break;
          if (g_dwCfgSwapCharCount != 0) {
            if (g_abCfgSwapCharTable == bVar18) {
              iVar7 = 0;
            }
            else {
              iVar7 = 0;
              do {
                iVar7 = iVar7 + 1;
                if (iVar7 == g_dwCfgSwapCharCount) goto LAB_20019604;
              } while ((&g_abCfgSwapCharTable)[iVar7 * 2] != bVar18);
            }
            pbVar30[iVar33] = (&DAT_2008a9dd)[iVar7 * 2];
          }
LAB_20019604:
          iVar33 = iVar33 + 1;
        } while (iVar33 != 0x1000);
        DAT_200723f0 = 0;
        if (g_protocol_2 != 0) {
          g_dwPageNeedsTeardown = 1;
          pbVar30 = cmd_dl_handler_alt((char *)pbVar30);
        }
        if (g_protocol_1 != 0) {
          pbVar30 = cmd_dl_handler((char *)pbVar30);
        }
        if (g_dwSlotSkipBody != 0) {
          pbVar6[4] = pbVar6[4] - (char)((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1)
          ;
        }
        DAT_200723f0 = 0;
        uVar35 = ZEXT48(pbVar30);
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0x82:
      uVar22 = parse_digits(pbVar29,3);
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        uVar16 = parse_digits(pbVar6 + 7,3);
        if (uVar16 == 0xffffffff) {
          cmd_flags = cmd_flags | 2;
          pbVar17 = pbVar6 + 7;
          uVar35 = 0xffffffff;
          uVar21 = g_dwCfgFxSlowdown;
        }
        else {
          uVar8 = parse_digits(pbVar6 + 0xb,3);
          if (uVar8 == 0xffffffff) {
            cmd_flags = cmd_flags | 2;
            pbVar17 = pbVar6 + 0xb;
            uVar35 = 0xffffffff;
            uVar21 = g_dwCfgFxSlowdown;
          }
          else {
            uVar31 = parse_digits(pbVar6 + 0xf,3);
            if (uVar31 == 0xffffffff) {
              cmd_flags = cmd_flags | 2;
              pbVar17 = pbVar6 + 0xf;
              uVar35 = 0xffffffff;
              uVar21 = g_dwCfgFxSlowdown;
            }
            else {
              uVar14 = parse_digits(pbVar6 + 0x13,3);
              if (uVar14 == 0xffffffff) {
                cmd_flags = cmd_flags | 2;
                pbVar17 = pbVar6 + 0x13;
                uVar35 = 0xffffffff;
                uVar21 = g_dwCfgFxSlowdown;
              }
              else {
                iVar33 = parse_digits(pbVar6 + 0x17,3);
                if (iVar33 == -1) {
                  cmd_flags = cmd_flags | 2;
                  pbVar17 = pbVar6 + 0x17;
                  uVar35 = 0xffffffff;
                  uVar21 = g_dwCfgFxSlowdown;
                }
                else {
                  iVar33 = parse_digits(pbVar6 + 0x1b,3);
                  uVar21 = g_dwCfgFxSlowdown;
                  if (iVar33 == -1) {
                    cmd_flags = cmd_flags | 2;
                    pbVar17 = pbVar6 + 0x1b;
                    uVar35 = 0xffffffff;
                  }
                  else {
                    pbVar17 = pbVar6 + 0x1e;
                    uVar35 = (ulonglong)g_dwActivePageIdx;
                    if (g_dwActivePageIdx != 0xffffffff) {
                      if (g_dwGfxRecHasGraphics[g_dwActivePageIdx].dwPage == 0) {
                        g_dwCmdErrorCode =
                             graphics_install(g_dwActivePageIdx,uVar16,uVar8,uVar31,uVar14,uVar22);
                        uVar35 = (ulonglong)g_dwCmdErrorCode;
                        *(undefined4 *)&g_dwGfxRecHasGraphics[g_dwActivePageIdx].field_0x1c4 = 1;
                        uVar21 = g_dwCfgFxSlowdown;
                      }
                      else {
                        g_dwCmdErrorCode =
                             graphics_install(g_dwActivePageIdx,uVar16,uVar8,uVar31,uVar14,uVar22);
                        uVar35 = CONCAT44(g_dwActivePageIdx,g_dwCmdErrorCode);
                        *(int *)&g_dwGfxRecHasGraphics[g_dwActivePageIdx].field_0x1c4 =
                             *(int *)&g_dwGfxRecHasGraphics[g_dwActivePageIdx].field_0x1c4 + 1;
                        uVar21 = g_dwCfgFxSlowdown;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      break;
    case 0x83:
      uVar8 = parse_digits(pbVar29,3);
      uVar16 = g_dwActivePageIdx;
      uVar22 = g_dwCfgPixels;
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar8 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else if (g_dwActivePageIdx == 0xffffffff) {
        g_dwCmdErrorCode = 0xff000002;
        uVar35 = (ulonglong)uVar8;
      }
      else if (g_dwGfxRecHasGraphics[g_dwActivePageIdx].dwPage == 0) {
        uVar21 = division(g_dwCfgChannels * g_dwCfgRowsPerLine,g_dwCfgColours);
        uVar21 = graphics_install(uVar16,0,0,uVar22,uVar21,uVar8);
        uVar22 = g_dwActivePageIdx;
        g_dwGfxRecHasGraphics[g_dwActivePageIdx].pSlot_id_array[0xf] = 1;
        *(undefined4 *)&g_dwGfxRecHasGraphics[uVar22].field_0x1c4 = 1;
        uVar35 = (ulonglong)uVar21;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else if (g_dwGfxRecHasGraphics[g_dwActivePageIdx].dwSlot_count < 0x10) {
        g_dwGfxRecHasGraphics[g_dwActivePageIdx].dwSlot_count =
             g_dwGfxRecHasGraphics[g_dwActivePageIdx].dwSlot_count + 1;
        uVar22 = g_dwActivePageIdx;
        uVar21 = g_dwGfxRecHasGraphics[g_dwActivePageIdx].dwSlot_count;
        g_dwGfxRecHasGraphics[g_dwActivePageIdx].pH_array[uVar21 + 0xf] = uVar8;
        g_dwGfxRecHasGraphics[uVar22].pSlot_id_array[uVar21 + 0xf] = 1;
        *(int *)&g_dwGfxRecHasGraphics[uVar22].field_0x1c4 =
             *(int *)&g_dwGfxRecHasGraphics[uVar22].field_0x1c4 + 1;
        g_dwGfxRecHasGraphics[uVar22].dwTerminator = 1;
        uVar35 = 0x2054daf8;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        g_dwCmdErrorCode = g_dwActivePageIdx << 0x18 | 0x62 | uVar8 << 0x10;
        uVar35 = 0x1d42054daf8;
      }
      break;
    case 0x84:
      uVar22 = parse_digits(pbVar29,3);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else {
        pbVar17 = pbVar6 + 6;
        if (g_dwActivePageIdx == 0xffffffff) {
          g_dwCmdErrorCode = 0xff000002;
          uVar35 = (ulonglong)uVar22;
        }
        else {
          uVar35 = (ulonglong)uVar22;
          if (g_dwGfxRecHasGraphics[g_dwActivePageIdx].dwPage != 0) {
            uVar21 = g_dwGfxRecHasGraphics[g_dwActivePageIdx].dwSlot_count;
            g_dwGfxRecHasGraphics[g_dwActivePageIdx].pSlot_id_array[uVar21 + 0xf] =
                 uVar22 + g_dwGfxRecHasGraphics[g_dwActivePageIdx].pSlot_id_array[uVar21 + 0xf];
            uVar35 = CONCAT44(uVar21,uVar22);
            uVar21 = g_dwCfgFxSlowdown;
          }
        }
      }
      break;
    case 0x86:
      uVar16 = parse_decimal_packed((int)pbVar29);
      pbVar17 = pbVar29 + (uVar16 & 0xf);
      uVar22 = uVar16 >> 4;
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar16;
      }
      else {
        uVar35 = (ulonglong)uVar16;
        if (g_dwSlotSkipBody == 0) {
          if (g_dwCfgIgnoreDp != 0) {
            uVar22 = 0;
          }
          uVar35 = (ulonglong)uVar16;
          if (g_dwActivePageIdx != 0xffffffff) {
            if ((g_dwCfgDoublesided == 0) || (g_protocol_1 != 0)) {
              if (uVar22 == 0) goto LAB_200193f0;
LAB_20019418:
              uVar21 = g_dwActivePageIdx;
              (&g_dwPageRecDwellPrimary)[g_dwActivePageIdx * 0x3f] = uVar22;
              (&g_dwPageRecDwellMirror)[uVar21 * 0x3f] = uVar22;
            }
            else {
              if (uVar22 != 0) {
                uVar21 = (&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode];
                (&g_dwPageRecDwellPrimary)[(g_dwActivePageIdx - (uVar21 >> 1)) * 0x3f] = uVar22;
                (&g_dwPageRecDwellMirror)[(g_dwActivePageIdx - (uVar21 >> 1)) * 0x3f] = uVar22;
                goto LAB_20019418;
              }
              iVar33 = g_dwActivePageIdx -
                       ((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1);
              (&g_dwPageRecDwellPrimary)[iVar33 * 0x3f] = 0;
              (&g_dwPageRecDwellMirror)[iVar33 * 0x3f] = 0;
LAB_200193f0:
              uVar21 = g_dwActivePageIdx;
              (&g_dwPageRecDwellPrimary)[g_dwActivePageIdx * 0x3f] = 0;
              (&g_dwPageRecDwellMirror)[uVar21 * 0x3f] = 0;
            }
            uVar16 = g_dwActivePageIdx;
            uVar35 = CONCAT44(g_dwActivePageIdx,&DAT_2054daf8);
            uVar21 = g_dwCfgFxSlowdown;
            if (g_dwGfxRecHasGraphics[g_dwActivePageIdx].dwPage != 0) {
              uVar8 = g_dwGfxRecHasGraphics[g_dwActivePageIdx].dwSlot_count;
              uVar21 = division(0x8ca00,g_dwCfgRowsPerLine * g_bright_clock_ctrl);
              g_dwGfxRecHasGraphics[uVar16].pSlot_id_array[uVar8 + 0xf] =
                   uVar21 * uVar22 + g_dwGfxRecHasGraphics[uVar16].pSlot_id_array[uVar8 + 0xf];
              uVar35 = (ulonglong)uVar21;
              uVar21 = g_dwCfgFxSlowdown;
            }
          }
        }
      }
      break;
    case 0x87:
      uVar35 = CONCAT44(uVar22,param_1);
      if (g_dwActivePageIdx != 0xffffffff) {
        (&g_dwPageRecReadyForRender)[g_dwActivePageIdx * 0x3f] = 0;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0x90:
      if (g_protocol_7 == 0) {
        uVar22 = parse_digits(pbVar29,3);
        pbVar17 = pbVar6 + 6;
      }
      else {
        uVar22 = parse_digits(pbVar29,2);
        pbVar17 = pbVar6 + 5;
      }
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 < 0x328) {
        if (*pbVar17 == 0x3c) {
          local_38 = &DAT_200c53b0;
          local_34 = 0;
          local_30 = 0x1000;
          pbVar17 = markup_compile(pbVar17 + 1,(int *)&local_38,0);
          if (g_protocol_7 == 0) {
            puVar9 = (undefined4 *)(&DAT_2055b000 + uVar22 * 0x1000);
            memcpy(puVar9,(undefined4 *)&DAT_200c53b0,0x1000);
            (&DAT_200cf5a8)[uVar22] = 0;
            (&DAT_200ce908)[uVar22] = 1;
            uVar35 = ZEXT48(puVar9);
            uVar21 = g_dwCfgFxSlowdown;
          }
          else {
            puVar9 = (undefined4 *)(uVar22 * 0x1000 + 0x205bf000);
            memcpy(puVar9,(undefined4 *)&DAT_200c53b0,0x1000);
            iVar33 = uVar22 + 100;
            (&DAT_200cf5a8)[iVar33] = 0;
            (&DAT_200ce908)[iVar33] = 1;
            uVar35 = CONCAT44(iVar33,puVar9);
            uVar21 = g_dwCfgFxSlowdown;
          }
        }
        else {
          cmd_flags = cmd_flags | 8;
          pbVar17 = pbVar17 + 1;
          uVar35 = (ulonglong)uVar22;
        }
      }
      else {
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      break;
    case 0x91:
      uVar22 = parse_digits(pbVar29,3);
      uVar16 = parse_digits(pbVar6 + 7,3);
      uVar8 = parse_digits(pbVar6 + 0xb,3);
      uVar21 = g_dwCfgFxSlowdown;
      if ((((uVar22 < 0x19 && uVar16 != 0xffffffff) && (uVar8 != 0xffffffff && uVar16 != 0)) &&
          (uVar8 != 0)) && (uVar16 * uVar8 < 0x4001)) {
        pbVar17 = pbVar6 + 0xf;
        if (pbVar6[0xe] == 0x3c) {
          pbVar30 = &DAT_200815e8;
          pbVar6 = (byte *)memfill((undefined4 *)&DAT_200815e8,0x1010101,0x4000);
          uVar21 = uVar16 >> 1;
          if (uVar8 != 0) {
            uVar31 = 0;
            while( true ) {
              pbVar6 = pbVar30;
              if (uVar21 != 0) {
                uVar14 = 0;
                do {
                  bVar18 = pbVar17[uVar14];
                  uVar2 = (bVar18 & 0x38) >> 3;
                  if ((uVar2 & 4) == 0) {
                    bVar24 = (byte)((uVar2 & 3) << 1);
                  }
                  else {
                    bVar24 = 1;
                  }
                  if ((bVar18 & 4) == 0) {
                    iVar33 = (bVar18 & 3) << 1;
                  }
                  else {
                    iVar33 = 1;
                  }
                  *pbVar6 = bVar24 | (byte)(iVar33 << 4);
                  uVar14 = uVar14 + 1;
                  pbVar6 = pbVar6 + 1;
                } while (uVar14 != uVar21);
                pbVar17 = pbVar17 + uVar21;
                pbVar6 = pbVar30 + uVar21;
              }
              if ((uVar16 & 1) != 0) {
                uVar14 = (*pbVar17 & 0x38) >> 3;
                if ((uVar14 & 4) == 0) {
                  bVar18 = (byte)(uVar14 << 1) & 6;
                }
                else {
                  bVar18 = 1;
                }
                pbVar17 = pbVar17 + 1;
                *pbVar6 = bVar18 | 0x10;
                pbVar30 = pbVar30 + 1;
              }
              uVar31 = uVar31 + 1;
              if (uVar31 == uVar8) break;
              pbVar30 = pbVar30 + uVar21;
            }
          }
          if (*pbVar17 == 0x3e) {
            g_dwSpriteHeader[uVar22] = uVar16 | 0x80000000 | uVar8 << 0x10;
            puVar9 = (undefined4 *)(&DAT_20887000 + uVar22 * 0x4000);
            memcpy(puVar9,(undefined4 *)&DAT_200815e8,0x4000);
            pbVar17 = pbVar17 + 1;
            uVar35 = ZEXT48(puVar9);
            uVar21 = g_dwCfgFxSlowdown;
          }
          else {
            cmd_flags = cmd_flags | 8;
            pbVar17 = pbVar17 + 1;
            uVar35 = ZEXT48(pbVar6);
            uVar21 = g_dwCfgFxSlowdown;
          }
        }
        else {
          cmd_flags = cmd_flags | 8;
          uVar35 = (ulonglong)uVar8;
        }
      }
      else {
        cmd_flags = cmd_flags | 2;
        pbVar17 = pbVar6 + 0xe;
        uVar35 = (ulonglong)uVar8;
      }
      break;
    case 0xc0:
      if (*pbVar29 == 0x2b) {
        DAT_20085664 = 1;
        pbVar17 = pbVar6 + 4;
        uVar35 = CONCAT44(uVar22,param_1);
      }
      else if (*pbVar29 == 0x2d) {
        DAT_20085664 = 0;
        pbVar17 = pbVar6 + 4;
        uVar35 = CONCAT44(uVar22,param_1);
      }
      else {
        uVar22 = cmd_qF_handler(pbVar29);
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0xc1:
      if (*pbVar29 == 0x50 || *pbVar29 == 0x20) {
        do {
          pbVar29 = pbVar29 + 1;
        } while (*pbVar29 == 0x50 || *pbVar29 == 0x20);
      }
      pbVar17 = pbVar29 + 2;
      if (pbVar29[2] == 0x21 || pbVar29[2] == 0) {
        uVar22 = parse_digits(pbVar29,2);
      }
      else {
        pbVar17 = pbVar29 + 3;
        if (pbVar29[3] != 0x21 && pbVar29[3] != 0) {
          g_dwCmdErrorCode = 0xea;
          cmd_flags = cmd_flags | 2;
          pbVar17 = pbVar29;
          uVar35 = CONCAT44(uVar22,param_1);
          break;
        }
        uVar22 = parse_digits(pbVar29,3);
      }
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 < 0x32) {
        g_dwCmdErrorCode = 0xeb;
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      else if (uVar22 < 0x259) {
        g_bright_clock_ctrl = division(0x8ca00,g_dwCfgRowsPerLine * uVar22);
        uVar35 = ISR_drive_setup(g_bright_clock_ctrl,extraout_r1);
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        g_dwCmdErrorCode = 0xec;
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      break;
    case 0xc2:
      if (*pbVar29 == 0x50 || *pbVar29 == 0x20) {
        do {
          pbVar29 = pbVar29 + 1;
        } while (*pbVar29 == 0x50 || *pbVar29 == 0x20);
      }
      pbVar17 = pbVar29 + 1;
      if (pbVar29[1] == 0x21 || pbVar29[1] == 0) {
        uVar21 = parse_digits(pbVar29,1);
      }
      else {
        pbVar17 = pbVar29 + 2;
        if (pbVar29[2] != 0x21 && pbVar29[2] != 0) {
          g_dwCmdErrorCode = 0xed;
          cmd_flags = cmd_flags | 2;
          pbVar17 = pbVar29;
          uVar35 = CONCAT44(uVar22,param_1);
          break;
        }
        uVar21 = parse_digits(pbVar29,2);
      }
      uVar35 = (ulonglong)uVar21;
      if (9 < uVar21) {
        g_dwCmdErrorCode = 0xee;
        cmd_flags = cmd_flags | 2;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0xc4:
      uVar22 = parse_digits(pbVar29,4);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else {
        pbVar17 = pbVar6 + 7;
        uVar35 = (ulonglong)uVar22;
        if (uVar22 - 2 < 4999) {
          DAT_20031890 = uVar22;
        }
      }
      break;
    case 0xc5:
      pbVar17 = cmd_Fm_handler(pbVar29);
      uVar35 = ZEXT48(pbVar17);
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0xd0:
      iVar33 = parse_digits(pbVar29,1);
      uVar21 = g_dwCfgFxSlowdown;
      if (iVar33 == -1) {
        g_dwCmdErrorCode = 0xa5;
        cmd_flags = cmd_flags | 2;
        uVar35 = CONCAT44(iVar33,iVar33);
      }
      else {
        uVar35 = CONCAT44(iVar33,iVar33);
        if (g_dwCfgDdxFixedLineSet != 0) {
          if (iVar33 == 0) {
            uVar22 = page_slot_set_active(g_dwCfgDdxFixedLine,0);
            uVar35 = (ulonglong)uVar22;
            uVar21 = g_dwCfgFxSlowdown;
          }
          else {
            uVar35 = CONCAT44(iVar33,iVar33);
            if (iVar33 == 1) {
              if ((g_dwCfgDoublesided != 0) && (g_protocol_1 == 0)) {
                g_dwPageNeedsTeardown = 1;
                FUN_20012208(g_dwCfgDdxFixedLine +
                             ((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1));
              }
              uVar22 = FUN_20012208(g_dwCfgDdxFixedLine);
              uVar35 = (ulonglong)uVar22;
              uVar21 = g_dwCfgFxSlowdown;
            }
          }
        }
      }
      break;
    case 0xd1:
      pbVar6 = DAT_200815e4 + 1;
      *DAT_200815e4 = 0x3a;
      DAT_200815e4 = pbVar6;
      DAT_200815e4 = (byte *)utoa((int)pbVar6,1,
                                  (&g_dwPageRecScheduleMark)[g_dwCfgDdxFixedLine * 0x3f]);
      uVar35 = ZEXT48(DAT_200815e4);
      *DAT_200815e4 = 0;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0xd2:
      uVar22 = cmd_qe_rl_handler();
      uVar35 = (ulonglong)uVar22;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0xd4:
      if (g_protocol_7 == 0) goto switchD_2001632c_caseD_5c;
      g_dwSlotSkipBody = 1;
      uVar35 = CONCAT44(uVar22,param_1);
      DAT_200855ec = pbVar29;
      break;
    case 0xe0:
      goto switchD_2001632c_caseD_e0;
    case 0xe1:
      uVar22 = led_test();
      uVar35 = (ulonglong)uVar22;
      uVar21 = g_dwCfgFxSlowdown;
      break;
    case 0xf0:
      cmd_zr_handler();
      DAT_2003171c = 1;
      parse_config();
      DAT_2003171c = 0;
      uVar22 = FUN_200268c0();
      uVar35 = (ulonglong)uVar22;
      uVar21 = g_dwCfgFxSlowdown;
      if (g_dwCfgDdxFixedLineSet != 0) {
        if ((g_dwCfgDoublesided != 0) && (g_protocol_1 == 0)) {
          g_dwPageNeedsTeardown = 1;
          FUN_20012208(g_dwCfgDdxFixedLine +
                       ((uint)(&g_dwCfgDlmxLinesPerIndex)[g_dwCfgCurrentMode] >> 1));
        }
        uVar22 = FUN_20012208(g_dwCfgDdxFixedLine);
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0xf1:
      DAT_20072374 = 0;
      DAT_20072378 = 1;
      uVar35 = CONCAT44(uVar22,param_1);
      break;
    case 0xf2:
      uVar22 = parse_digits(pbVar29,1);
      if ((uVar22 == 0xffffffff) || (uVar22 = uVar22 - 1, 7 < uVar22)) {
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        uVar22 = cmd_zp_handler();
        pbVar17 = pbVar6 + 4;
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0xf3:
      uVar22 = hex_to_bin(pbVar29);
      if (uVar22 == 0xffffffff) {
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        DAT_20072418 = uVar22;
        uVar22 = fpga_reg34_write(uVar22);
        pbVar17 = pbVar6 + 4;
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      break;
    case 0xf4:
      uVar22 = parse_digits(pbVar29,1);
      uVar21 = g_dwCfgFxSlowdown;
      if (uVar22 == 0xffffffff) {
        g_dwCmdErrorCode = 0xa0;
        cmd_flags = cmd_flags | 2;
        uVar35 = 0xffffffff;
      }
      else if (uVar22 == 0) {
        g_dwCmdErrorCode = 0xa1;
        cmd_flags = cmd_flags | 2;
        uVar35 = 0;
      }
      else if (uVar22 < 8) {
        g_protocol_5 = 0;
        g_protocol_1 = 0;
        g_protocol_4 = 0;
        g_protocol_7 = 0;
        g_protocol_2 = 0;
        g_protocol_3 = 0;
        switch(uVar22) {
        case 1:
          g_protocol_1 = 1;
          break;
        case 2:
          g_protocol_2 = 1;
          break;
        case 3:
          g_protocol_3 = 1;
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
        mem_init();
        g_dwCfgCurrentMode = 1;
        uVar35 = (ulonglong)uVar22;
        uVar21 = g_dwCfgFxSlowdown;
      }
      else {
        g_dwCmdErrorCode = 0xa2;
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      break;
    case 0xf8:
      uVar35 = CONCAT44(uVar22,param_1);
      if ((param_1[0x10] == 0x30) && (uVar35 = CONCAT44(uVar22,param_1), param_1[0x11] != 0x40)) {
        FUN_2000ddf8(param_1);
        USART_wait_tx_done((uint)*param_1);
        gpbr_set_word(0,5);
        gpbr_set_word(1,(uint)*param_1);
        uVar22 = read_dip_switches();
        if ((uVar22 & 0x80) == 0) {
          uVar15 = 0x2580;
        }
        else {
          uVar15 = 0x4b00;
        }
        gpbr_set_word(2,uVar15);
        system_reset();
        goto switchD_2001632c_caseD_fb;
      }
      break;
    case 0xf9:
switchD_2001632c_caseD_f9:
      FUN_2000ddf8(param_1);
      USART_wait_tx_done((uint)*param_1);
      system_reset();
switchD_2001632c_caseD_e0:
      uVar22 = parse_digits(pbVar29,1);
      uVar21 = g_dwCfgFxSlowdown;
      if ((uVar22 == 0xffffffff) || (9 < uVar22)) {
        cmd_flags = cmd_flags | 2;
        uVar35 = (ulonglong)uVar22;
      }
      else {
        pbVar17 = pbVar6 + 4;
        uVar35 = (ulonglong)uVar22;
        DAT_200722b4 = uVar22;
      }
      break;
    case 0xfa:
switchD_2001632c_caseD_fa:
      uVar35 = ZEXT48(pbVar12);
      uVar21 = g_dwCfgFxSlowdown;
      if ((param_1[0x10] == 0x30) && (uVar35 = ZEXT48(pbVar12), param_1[0x11] != 0x40)) {
        FUN_2000ddf8(param_1);
        USART_wait_tx_done((uint)*param_1);
        gpbr_set_word(0,2);
        system_reset();
        goto switchD_2001632c_caseD_f9;
      }
      break;
    case 0xfb:
switchD_2001632c_caseD_fb:
      uVar35 = ZEXT48(param_1);
      uVar21 = g_dwCfgFxSlowdown;
      if ((param_1[0x10] == 0x30) && (uVar35 = ZEXT48(param_1), param_1[0x11] != 0x40)) {
        FUN_2000ddf8(param_1);
        USART_wait_tx_done((uint)*param_1);
        gpbr_set_word(0,3);
        gpbr_set_word(1,(uint)*param_1);
        uVar22 = read_dip_switches();
        if ((uVar22 & 0x80) == 0) {
          uVar15 = 0x2580;
        }
        else {
          uVar15 = 0x4b00;
        }
        gpbr_set_word(2,uVar15);
        pbVar12 = (byte *)system_reset();
        goto switchD_2001632c_caseD_fa;
      }
      break;
    case 0xfd:
      DAT_20072414 = 0;
      uVar35 = CONCAT44(uVar22,param_1);
    }
switchD_2001632c_caseD_1e:
    g_dwCfgFxSlowdown = uVar21;
  } while( true );
}

