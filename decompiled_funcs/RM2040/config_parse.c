
void config_parse(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  dword dVar4;
  byte bVar5;
  char *pcVar6;
  byte *pbVar7;
  code *pcVar8;
  byte *pbVar9;
  dword *pdVar10;
  dword *pdVar11;
  int *piVar12;
  undefined4 *puVar13;
  uint uVar14;
  undefined4 extraout_r1;
  uint uVar15;
  int iVar16;
  char cVar17;
  int iVar18;
  int iVar19;
  undefined4 *puVar20;
  uint uVar21;
  undefined4 local_228;
  int local_208 [120];
  dword local_28;
  uint local_24;

  piVar12 = &local_228;
  puVar13 = &local_228;
  uVar14 = 0;
  g_timeout_command_string._0_1_ = 0;
  g_bright_clock_ctrl = 0x5a0;
  g_fixed_font_flag = 4;
  g_start_timed_out = 1;
  DAT_20174678 = 0;
  g_current_mode = 0x49;
  g_doublesided = 0;
  g_cap_brightness = 0xffffffff;
  g_debug_flag = 0;
  g_ISR_timer1_gate = 0;
  twi_string.str[0] = '\0';
  if (g_channels != 0) {
    do {
      (&DAT_20187638)[uVar14] = 0;
      uVar14 = uVar14 + 1;
    } while (uVar14 < g_channels);
  }
  iVar18 = 0;
  g_temp_probe_enable = 0;
  DAT_20189678 = 0;
  DAT_2018df6c = 0;
  do {
    (&g_char_remap)[iVar18] = (char)iVar18;
    iVar18 = iVar18 + 1;
  } while (iVar18 != 0x100);
  iVar18 = 0;
  do {
    *(undefined4 *)((int)&g_zone_line_count + iVar18) = 0;
    iVar18 = iVar18 + 4;
  } while (iVar18 != 0x40);
  iVar18 = 0;
  do {
    puVar20 = &g_zone_x + iVar18 * 0xa4;
    iVar16 = 0;
    do {
      *puVar20 = 0;
      puVar20[1] = 0;
      puVar20[2] = 0;
      puVar20[3] = 0;
      iVar16 = iVar16 + 1;
      puVar20 = puVar20 + 4;
    } while (iVar16 != 0x29);
    iVar18 = iVar18 + 1;
  } while (iVar18 != 0x10);
  iVar18 = 0;
  do {
    iVar19 = iVar18;
    iVar16 = 0;
    *(undefined4 *)((int)&g_missing_leds + iVar19) = 0;
    iVar18 = iVar19 + 4;
  } while (iVar19 + 4 != 0x20);
  g_zone_count = 0;
  g_suppress_hour_zero = 0;
  g_suppress_min_zero = 0;
  g_suppress_sec_zero = 0;
  g_suppress_day_zero = 0;
  g_replace_hours_zero = 0;
  g_suppress_mon_zero = 0;
  g_fixed_content_def_mode = iVar19 + -0x1b;
  g_msg_mode = iVar19 + -0x1a;
  DAT_2017471c = 0;
  DAT_20174550 = 0;
  do {
    *(undefined4 *)((int)&g_channel_lengths + iVar16) = 0;
    *(undefined4 *)((int)&g_channel_pixels + iVar16) = 0;
    *(undefined4 *)((int)&g_lines_per_channel + iVar16) = 1;
    iVar16 = iVar16 + 4;
  } while (iVar16 != 0x20);
  iVar18 = 0;
  do {
    (&DAT_201896c0)[iVar18] = 0;
    iVar18 = iVar18 + 1;
  } while (iVar18 != 0x4800);
  g_speed_a = 0x46;
  g_speed_b = 0x1e;
  g_fx_slowdown = 0;
  g_brightness = 0;
  g_msg_timeout_ms = 2000;
  conf_pix_count = 0x100;
  g_pixels = 0x100;
  g_flash = 0;
  g_channels = 8;
  g_colours = 1;
  g_rows_per_line = 8;
  g_swap_char = 'O';
  g_scroll_if_too_wide = 1;
  DAT_20174570 = 0;
  fpga_flags = fpga_flags | 0x80000000;
  FUN_200004d0(1,0x48);
  g_uart_baud_port1 = 0;
  g_uart_baud_port2 = 0;
  memfill(&g_conf_file_dest.magic,0xff,0x2000);
  g_ligature_count = 0;
  local_28 = 0;
  iVar18 = SPI0_transfer_file(0,(byte *)&g_conf_file_dest,(char  [4])ACFG);
  if (iVar18 == 0) {
    bVar2 = false;
    bVar3 = false;
    LAB_20012564:
    if (g_next_bus_ddx == 1) {
      g_master_mode = 0;
    }
    if (bVar2) {
      local_28 = 0;
      if (g_channels != 0) {
        do {
          if (conf_pix_count < (uint)(&g_channel_lengths)[local_28]) {
            conf_pix_count = (&g_channel_lengths)[local_28];
          }
          local_28 = local_28 + 1;
        } while (local_28 < g_channels);
      }
    }
    else {
      local_28 = 0;
      if (g_channels != 0) {
        do {
          (&g_channel_lengths)[local_28] = conf_pix_count;
          local_28 = local_28 + 1;
        } while (local_28 < g_channels);
      }
    }
    local_28 = 0;
    if (g_channels != 0) {
      do {
        if (g_max_lines < (uint)(&g_lines_per_channel)[local_28]) {
          g_max_lines = (&g_lines_per_channel)[local_28];
        }
        local_28 = local_28 + 1;
      } while (local_28 < g_channels);
    }
    switch(g_max_lines) {
    case 1:
      g_block_size = 0x800;
      break;
    case 2:
      g_block_size = 0x400;
      break;
    case 3:
    case 4:
      g_block_size = 0x200;
      break;
    case 5:
    case 6:
    case 7:
    case 8:
      g_block_size = 0x100;
      break;
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
      g_block_size = 0x80;
    }
    if ((char)g_drive_type == 'M') {
      uVar14 = conf_pix_count + 0x7f;
      local_28 = 0;
      if (g_channels != 0) {
        do {
          (&g_channel_pixels)[local_28] = uVar14 & 0xffffff80;
          local_28 = local_28 + 1;
        } while (local_28 < g_channels);
      }
    }
    else if (((char)g_drive_type == 'T') || ((char)g_drive_type == 'D')) {
      uVar14 = conf_pix_count + 0x1f;
      local_28 = 0;
      if (g_channels != 0) {
        do {
          (&g_channel_pixels)[local_28] = uVar14 & 0xffffffe0;
          local_28 = local_28 + 1;
        } while (local_28 < g_channels);
      }
    }
    if (g_colours == 2) {
      g_buf_stride1 = g_block_size * g_max_lines * g_rows_per_line * 4 >> 3;
      g_buf_stride2 = 0;
    }
    else if (g_colours == 3) {
      g_buf_stride1 = g_block_size * g_rows_per_line * g_max_lines * 2 >> 3;
      g_buf_stride2 = g_block_size * g_rows_per_line * g_max_lines * 4 >> 3;
    }
    else if (g_colours == 1) {
      g_buf_stride1 = 0;
      g_buf_stride2 = 0;
    }
    conf_lines = 0;
    local_28 = 0;
    if (g_channels != 0) {
      do {
        conf_lines = (&g_lines_per_channel)[local_28] + conf_lines;
        local_28 = local_28 + g_colours;
      } while (local_28 < g_channels);
    }
    if (g_doublesided != 0) {
      conf_lines = conf_lines >> 1;
    }
    uVar14 = DAT_2018df78;
    if (DAT_20192278 == 0) {
      local_28 = 0;
      uVar14 = 0;
      if (conf_lines != 0) {
        local_28 = 0;
        do {
          dVar4 = g_rows_per_line;
          *(dword *)(&DAT_20192274 + local_28 * 0x10) = g_rows_per_line * local_28;
          (&DAT_20192278)[local_28 * 4] = dVar4;
          uVar14 = y_to_channel_idx((&g_zone_y)[local_28 * 4]);
          dVar4 = conf_pix_count;
          *(dword *)(&DAT_20192270 + local_28 * 0x10) =
          conf_pix_count - (&g_channel_lengths)[uVar14];
          *(dword *)(&DAT_2019227c + local_28 * 0x10) = dVar4 - (&g_zone_x)[local_28 * 4];
          local_28 = local_28 + 1;
          uVar14 = conf_lines;
        } while (local_28 < conf_lines);
      }
    }
    DAT_2018df78 = uVar14;
    if (!bVar3) {
      g_canvas_x_off = 0;
      g_canvas_y_off = 0;
      g_canvas_width = conf_pix_count;
      g_canvas_height = conf_lines * g_rows_per_line;
    }
    FUN_2000fcbc();
    g_fixed_font_flag = g_fixed_font_flag & 0xff;
    if (9 < g_fixed_font_flag) {
      g_fixed_font_flag = 4;
    }
    FUN_2000fed8(g_fixed_font_flag,extraout_r1);
    FUN_2000cfc0();
    uVar14 = g_block_size >> 3;
    memfill(&local_228,0,0x40);
    DAT_20174684 = 0;
    if (g_colours == 2) {
      g_buf_stride1 = uVar14 * g_max_lines * g_rows_per_line * 4;
      g_buf_stride2 = 0;
      piVar12 = local_208;
      uVar21 = 0;
      do {
        iVar18 = (uVar21 >> 1) * uVar14 * g_rows_per_line +
        (0x100 - ((uint)(&g_channel_pixels)[uVar21] >> 3));
        piVar12[-8] = iVar18;
        *piVar12 = iVar18;
        if ((uVar21 & 1) != 0) {
          piVar12[-8] = iVar18 + g_buf_stride1;
        }
        uVar21 = uVar21 + 1;
        piVar12 = piVar12 + 1;
      } while (uVar21 != 8);
    }
    else if (g_colours == 3) {
      g_buf_stride1 = uVar14 * g_rows_per_line * g_max_lines * 2;
      g_buf_stride2 = uVar14 * g_rows_per_line * g_max_lines * 4;
      piVar12 = local_208;
      uVar21 = 0;
      do {
        iVar18 = 0x100 - ((uint)(&g_channel_pixels)[uVar21] >> 3);
        piVar12[-8] = iVar18;
        *piVar12 = iVar18;
        if (2 < uVar21) {
          iVar18 = uVar14 * g_rows_per_line + iVar18;
          piVar12[-8] = iVar18;
          *piVar12 = iVar18;
        }
        if (uVar21 == 4 || uVar21 == 1) {
          piVar12[-8] = piVar12[-8] + g_buf_stride1;
        }
        if (uVar21 == 5 || uVar21 == 2) {
          piVar12[-8] = piVar12[-8] + g_buf_stride2;
        }
        uVar21 = uVar21 + 1;
        piVar12 = piVar12 + 1;
      } while (uVar21 != 6);
    }
    else if (g_colours == 1) {
      g_buf_stride1 = 0;
      g_buf_stride2 = 0;
      DAT_20174684 = 0x10;
      if ((char)g_drive_type == 'M') {
        uVar21 = 8;
      }
      else {
        uVar21 = 4;
      }
      uVar15 = 0;
      do {
        iVar18 = uVar15 * uVar14 * g_rows_per_line +
        (0x100 - ((uint)(&g_channel_pixels)[uVar15] >> 3));
        *piVar12 = iVar18;
        piVar12[8] = iVar18;
        uVar15 = uVar15 + 1;
        piVar12 = piVar12 + 1;
      } while (uVar15 < uVar21);
    }
    iVar18 = 0;
    do {
      *(uint *)((int)&DAT_201896a0 + iVar18) =
      *(uint *)((int)&local_228 + iVar18) | *(int *)((int)puVar13 + 0x20) << 0x10;
      iVar18 = iVar18 + 4;
      puVar13 = (undefined4 *)((int)puVar13 + 4);
    } while (iVar18 != 0x20);
    FUN_2000fb04();
    FUN_200096a0();
    g_test_pattern = 0;
    DAT_201746d8 = 0;
    g_dlmx = 1;
    return;
  }
  pdVar11 = &g_conf_file_dest.crc_start_offset;
  config_file_crc = g_conf_file_dest.checksum;
  bVar2 = false;
  iVar18 = 0;
  bVar1 = false;
  bVar3 = false;
  uVar14 = g_sequence_flags;
  switchD_20012400_caseD_47:
  do {
    g_sequence_flags = uVar14;
    pdVar11 = (dword *)FUN_2000d108((char *)pdVar11,(char *)&local_228,0x200);
    if ((pdVar11 == (dword *)0x0) || (((char)local_228 == '.' && (local_228._1_1_ == '\0'))))
      goto LAB_20012564;
    pcVar6 = strcmp_w_equals((char *)&local_228,"FixedUARTspeed=");
    if (pcVar6 == (char *)0x0) {
      pbVar7 = (byte *)strcmp_w_equals((char *)&local_228,"HygrosenTempProbe=");
      if (pbVar7 != (byte *)0x0) {
        if ((*pbVar7 & 0x5f) == 0x4e) {
          g_temp_probe_enable = 0;
        }
        else if ((*pbVar7 & 0x5f) == 0x59) {
          g_temp_probe_enable = 1;
        }
        DAT_20191fd8 = 2;
        pcVar8 = (code *)cfg_parse_base10((char *)pbVar7,(int *)&local_24);
        if (pcVar8 < UndefinedInstruction) {
          DAT_20191fd8 = local_24;
        }
        DAT_2018df40 = *pcVar8;
        uVar14 = g_sequence_flags;
        if (((byte)*pcVar8 & 0x5f) == 0x4e) {
          DAT_20191fdc = 0;
        }
        else {
          DAT_20191fdc = (uint)(((byte)*pcVar8 & 0x5f) == 0x59);
        }
        goto switchD_20012400_caseD_47;
      }
      pcVar6 = strcmp_w_equals((char *)&local_228,"NextBusSize=");
      if (pcVar6 == (char *)0x0) {
        pcVar6 = strcmp_w_equals((char *)&local_228,"NextBusDDX=");
        if (pcVar6 == (char *)0x0) {
          pcVar6 = strcmp_w_equals((char *)&local_228,"Clever-Devices-Zi=");
          if (pcVar6 == (char *)0x0) {
            pcVar6 = strcmp_w_equals((char *)&local_228,"FixedClockLine=");
            if (pcVar6 == (char *)0x0) {
              pcVar6 = strcmp_w_equals((char *)&local_228,"MLSlot=");
              if (pcVar6 == (char *)0x0) {
                pcVar6 = strcmp_w_equals((char *)&local_228,"Multi-Languages=");
                if (pcVar6 == (char *)0x0) {
                  pbVar7 = (byte *)strcmp_w_equals((char *)&local_228,"SilentFrameUpdate=");
                  if (pbVar7 == (byte *)0x0) {
                    pcVar6 = strcmp_w_equals((char *)&local_228,"LedErrorsMaxMin=");
                    if (pcVar6 != (char *)0x0) {
                      pbVar7 = cfg_parse_base10(pcVar6,(int *)&local_24);
                      g_led_err_max = local_24;
                      cfg_parse_base10((char *)(pbVar7 + 1),(int *)&local_24);
                      g_led_err_min = local_24;
                    }
                    pcVar6 = strcmp_w_equals((char *)&local_228,"MaxScrolls=");
                    if (pcVar6 != (char *)0x0) {
                      cfg_parse_base10(pcVar6,(int *)&local_24);
                      g_max_scrolls = local_24;
                    }
                    pbVar7 = (byte *)strcmp_w_equals((char *)&local_228,"FixedFontFlag=");
                    if (pbVar7 == (byte *)0x0) {
                      pcVar6 = strcmp_w_equals((char *)&local_228,"BaudOption=");
                      if (pcVar6 == (char *)0x0) {
                        pcVar6 = strcmp_w_equals((char *)&local_228,"DDXmodalPage=");
                        if (pcVar6 == (char *)0x0) {
                          pcVar6 = strcmp_w_equals((char *)&local_228,"DDXfixedLine=");
                          if (pcVar6 == (char *)0x0) {
                            pcVar6 = strcmp_w_equals((char *)&local_228,"DLMx=");
                            if (pcVar6 == (char *)0x0) {
                              pcVar6 = strcmp_w_equals((char *)&local_228,"CurrentMode=");
                              if (pcVar6 == (char *)0x0) {
                                pbVar7 = (byte *)strcmp_w_equals((char *)&local_228,
                                 "modeChangeClearsContent=");
                                if (pbVar7 == (byte *)0x0) {
                                  pbVar7 = (byte *)strcmp_w_equals((char *)&local_228,
                                   "autoDetectArabic=");
                                  if (pbVar7 == (byte *)0x0) {
                                    pbVar7 = (byte *)strcmp_w_equals((char *)&local_228,
                                     "translateArabic=");
                                    if (pbVar7 == (byte *)0x0) {
                                      pbVar7 = (byte *)strcmp_w_equals((char *)&local_228,
                                       "Succession=");
                                      if (pbVar7 == (byte *)0x0) {
                                        pcVar6 = strcmp_w_equals((char *)&local_228,"MainChannel=");
                                        if (pcVar6 == (char *)0x0) {
                                          pcVar6 = strcmp_w_equals((char *)&local_228,
                                           "defSeqEffect=");
                                          if (pcVar6 == (char *)0x0) {
                                            pbVar7 = (byte *)strcmp_w_equals((char *)&local_228,

                                              "CfgFixedContentDefMode=");
                                            if (pbVar7 == (byte *)0x0) {
                                              pbVar7 = (byte *)strcmp_w_equals((char *)&local_228,
                                               "internalMsgMode=");
                                              if (pbVar7 == (byte *)0x0) {
                                                pbVar7 = (byte *)strcmp_w_equals((char *)&local_228,
                                                 "scrollIfTooWide=")
                                                ;
                                                if (pbVar7 == (byte *)0x0) {
                                                  pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                    local_228,"truncateOnChar=");
                                                  if (pbVar7 == (byte *)0x0) {
                                                    pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                      local_228,"truncateOnWord=");
                                                    if (pbVar7 == (byte *)0x0) {
                                                      pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                        local_228,"suppressHourLeadingZero=");
                                                      if (pbVar7 == (byte *)0x0) {
                                                        pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                          local_228,"suppressMinsLeadingZero=");
                                                        if (pbVar7 == (byte *)0x0) {
                                                          pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                            local_228,"suppressSecsLeadingZero=");
                                                          if (pbVar7 == (byte *)0x0) {
                                                            pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                              local_228,"suppressDayLeadingZero=");
                                                            if (pbVar7 == (byte *)0x0) {
                                                              pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                local_228,"replaceHoursLeadingZero=");
                                                              if (pbVar7 == (byte *)0x0) {
                                                                pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                  local_228,"suppressMonLeadingZero=");
                                                                if (pbVar7 == (byte *)0x0) {
                                                                  pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                    local_228,"ArabicLigatures=");
                                                                  if (pbVar7 != (byte *)0x0) {
                                                                    do {
                                                                      local_28 = 0;
                                                                      if (DAT_2002387c != 0) {
                                                                        bVar5 = *pbVar7;
                                                                        while (bVar5 != 0x2c) {
                                                                          pbVar7 = (byte *)FUN_2000d05c(pbVar7,(int
                                                                            *)&local_24);
                                                                          iVar16 = g_ligature_count * 3;
                                                                          (&g_arabic_ligatures)[iVar16 + local_28] =
                                                                          (char)local_24;
                                                                          (&DAT_20187275)[iVar16 + local_28] = 0;
                                                                          if (*pbVar7 == 0x20) {
                                                                            pbVar7 = pbVar7 + 1;
                                                                          }
                                                                          local_28 = local_28 + 1;
                                                                          if (DAT_2002387c <= local_28) break;
                                                                          bVar5 = *pbVar7;
                                                                        }
                                                                      }
                                                                      pbVar9 = pbVar7 + 1;
                                                                      g_ligature_count = g_ligature_count + 1;
                                                                      local_28 = 0;
                                                                      if (DAT_2002387c != 0) {
                                                                        bVar5 = pbVar7[1];
                                                                        while (1 < bVar5 - 0x2c) {
                                                                          pbVar9 = (byte *)FUN_2000d05c(pbVar9,(int *)&
                                                                            local_24);
                                                                          iVar16 = g_ligature_count * 3;
                                                                          (&g_arabic_ligatures)[iVar16 + local_28] =
                                                                          (char)local_24;
                                                                          (&DAT_20187275)[iVar16 + local_28] = 0;
                                                                          if (*pbVar9 == 0x20) {
                                                                            pbVar9 = pbVar9 + 1;
                                                                          }
                                                                          local_28 = local_28 + 1;
                                                                          if (DAT_2002387c <= local_28) break;
                                                                          bVar5 = *pbVar9;
                                                                        }
                                                                      }
                                                                      g_ligature_count = g_ligature_count + 1;
                                                                      uVar14 = g_sequence_flags;
                                                                      if (*pbVar9 == 0x2d)
                                                                        goto switchD_20012400_caseD_47;
                                                                      pbVar7 = pbVar9 + 1;
                                                                    } while( true );
                                                                  }
                                                                  pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                    local_228,"ChannelLengths=");
                                                                  if (pbVar7 == (byte *)0x0) {
                                                                    pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                      local_228,"missingLEDs=");
                                                                    if (pbVar7 == (byte *)0x0) {
                                                                      pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                        local_228,"LinesPerChannel=");
                                                                      if (pbVar7 == (byte *)0x0) {
                                                                        pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                         "PSU=");
                                                                        if (pcVar6 == (char *)0x0) {
                                                                          pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                            local_228,"doublesided=");
                                                                          if (pbVar7 == (byte *)0x0) {
                                                                            pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                              local_228,"swapChar=");
                                                                            if (pbVar7 == (byte *)0x0) {
                                                                              pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                                local_228,"LightSensor=");
                                                                              if (pbVar7 == (byte *)0x0) {
                                                                                pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                 "LSType=");
                                                                                if (pcVar6 != (char *)0x0) {
                                                                                  if (*pcVar6 == '0') {
                                                                                    fpga_flags = fpga_flags & 0x7fffffff;
                                                                                    FUN_200004d0(0,0x48);
                                                                                  }
                                                                                  else {
                                                                                    fpga_flags = fpga_flags | 0x80000000;
                                                                                    FUN_200004d0(1,0x48);
                                                                                  }
                                                                                }
                                                                                pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                                  local_228,"Temp=");
                                                                                if (pbVar7 == (byte *)0x0) {
                                                                                  pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                                    local_228,"LEDmon=");
                                                                                  if (pbVar7 == (byte *)0x0) {
                                                                                    pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                                      local_228,"DriveType=");
                                                                                    if (pbVar7 == (byte *)0x0) {
                                                                                      pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                       "speedDivisorM=");
                                                                                      if (pcVar6 == (char *)0x0) {
                                                                                        pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                         "speedDivisorD=");
                                                                                        if (pcVar6 == (char *)0x0) {
                                                                                          pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                           "speedDivisorMB=");
                                                                                          if (pcVar6 == (char *)0x0) {
                                                                                            pcVar6 = strcmp_w_equals((char *)&
                                                                                              local_228,"speedDivisorDB=");
                                                                                            if (pcVar6 == (char *)0x0) {
                                                                                              pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                                                local_228,"BrightControl=");
                                                                                              if (pbVar7 == (byte *)0x0) {
                                                                                                pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                 "Pixels=");
                                                                                                if (pcVar6 == (char *)0x0) {
                                                                                                  pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                   "Channels=");
                                                                                                  if (pcVar6 == (char *)0x0) {
                                                                                                    pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                     "Colours=");
                                                                                                    if (pcVar6 == (char *)0x0) {
                                                                                                      pcVar6 = strcmp_w_equals((char *)&
                                                                                                        local_228,"RowsPerLine=");
                                                                                                      if (pcVar6 == (char *)0x0) {
                                                                                                        pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                         "Speed=");
                                                                                                        if (pcVar6 == (char *)0x0) {
                                                                                                          pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                           "FXslowdown=");
                                                                                                          if (pcVar6 == (char *)0x0) {
                                                                                                            pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                             "PROTOCOL=");
                                                                                                            if (pcVar6 == (char *)0x0) {
                                                                                                              pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                                                                local_228,"RGSwap=");
                                                                                                              if (pbVar7 == (byte *)0x0) {
                                                                                                                pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                                                                  local_228,"RBSwap=");
                                                                                                                if (pbVar7 != (byte *)0x0) {
                                                                                                                  uVar14 = g_sequence_flags;
                                                                                                                  if ((*pbVar7 & 0x5f) == 0x4e) {
                                                                                                                    conf_swap = conf_swap & 0xfffffffd;
                                                                                                                  }
                                                                                                                  else if ((*pbVar7 & 0x5f) == 0x59) {
                                                                                                                    conf_swap = conf_swap | 2;
                                                                                                                  }
                                                                                                                  goto switchD_20012400_caseD_47;
                                                                                                                }
                                                                                                                pbVar7 = (byte *)strcmp_w_equals((char *)&
                                                                                                                  local_228,"Master=");
                                                                                                                if (pbVar7 == (byte *)0x0) {
                                                                                                                  pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                                   "StartTimedOut=");
                                                                                                                  if (((pcVar6 == (char *)0x0) || (*pcVar6 != 'Y')
                                                                                                                    ) || (g_start_timed_out = 1,
                                                                                                                    uVar14 = g_sequence_flags,
                                                                                                                    pcVar6[1] != ' ' && pcVar6[1] != '\0'))
                                                                                                                  {
                                                                                                                    pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                                     "Timeout=");
                                                                                                                    if (pcVar6 == (char *)0x0) {
                                                                                                                      pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                                       "Sequence=");
                                                                                                                      if (pcVar6 == (char *)0x0) {
                                                                                                                        pcVar6 = strcmp_w_equals((char *)&
                                                                                                                          local_228,"Flash=");
                                                                                                                        if (pcVar6 == (char *)0x0) {
                                                                                                                          pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                                           "MaintTime=");
                                                                                                                          if (pcVar6 == (char *)0x0) {
                                                                                                                            pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                                             "PinLock=");
                                                                                                                            if (pcVar6 == (char *)0x0) {
                                                                                                                              pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                                               "MaxADC=");
                                                                                                                              if (pcVar6 == (char *)0x0) {
                                                                                                                                pcVar6 = strcmp_w_equals((char *)&
                                                                                                                                  local_228,"MinBr=");
                                                                                                                                if (pcVar6 == (char *)0x0) {
                                                                                                                                  pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                                                   "MaxBr=");
                                                                                                                                  if (pcVar6 == (char *)0x0) {
                                                                                                                                    pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                                                     "CapBr=");
                                                                                                                                    if (pcVar6 == (char *)0x0) {
                                                                                                                                      pcVar6 = strcmp_w_equals((char *)&local_228,
                                                                                                                                       "DST=");
                                                                                                                                      uVar14 = g_sequence_flags;
                                                                                                                                      if (pcVar6 != (char *)0x0) {
                                                                                                                                        pbVar7 = cfg_parse_base10(pcVar6,(int *)&
                                                                                                                                          local_24);
                                                                                                                                        g_dst_start_month = local_24;
                                                                                                                                        uVar14 = g_sequence_flags;
                                                                                                                                        if ((*pbVar7 == 0x2c) &&
                                                                                                                                         (g_dst_start_week = (uint)pbVar7[1],
                                                                                                                                           pbVar7[2] == 0x2c)) {
                                                                                                                                          pbVar7 = cfg_parse_base10((char *)(pbVar7 + 3),
                                                                                                                                            (int *)&local_24);
                                                                                                                                        g_dst_end_month = local_24;
                                                                                                                                        uVar14 = g_sequence_flags;
                                                                                                                                        if (*pbVar7 == 0x2c) {
                                                                                                                                          g_dst_end_week = (uint)pbVar7[1];
                                                                                                                                          g_dst_param4 = 2;
                                                                                                                                          g_dst_param5 = 1;
                                                                                                                                          if (pbVar7[2] == 0x2c) {
                                                                                                                                            pbVar7 = cfg_parse_base10((char *)(pbVar7 +
                                                                                                                                              3),(int *)&local_24);
                                                                                                                                            g_dst_param4 = local_24;
                                                                                                                                            uVar14 = g_sequence_flags;
                                                                                                                                            if (*pbVar7 != 0x2c)
                                                                                                                                              goto switchD_20012400_caseD_47;
                                                                                                                                            cfg_parse_base10((char *)(pbVar7 + 1),
                                                                                                                                             (int *)&local_24);
                                                                                                                                            g_dst_param5 = local_24;
                                                                                                                                          }
                                                                                                                                          g_dst_valid_marker = 0;
                                                                                                                                          uVar14 = g_sequence_flags;
                                                                                                                                          if ((((g_dst_start_month - 1 < 0xc) &&
                                                                                                                                           (g_dst_end_month - 1 < 0xc)) &&
                                                                                                                                            (g_dst_start_month < g_dst_end_month)) &&
                                                                                                                                           (true)) {
                                                                                                                                            switch(g_dst_start_week) {
                                                                                                                                            case 0x46:
                                                                                                                                              g_dst_start_week = 1;
                                                                                                                                              break;
                                                                                                                                            default:
                                                                                                                                              goto switchD_20012400_caseD_47;
                                                                                                                                            case 0x4c:
                                                                                                                                              g_dst_start_week = 5;
                                                                                                                                              break;
                                                                                                                                            case 0x51:
                                                                                                                                              g_dst_start_week = 4;
                                                                                                                                              break;
                                                                                                                                            case 0x53:
                                                                                                                                              g_dst_start_week = 2;
                                                                                                                                              break;
                                                                                                                                            case 0x54:
                                                                                                                                              g_dst_start_week = 3;
                                                                                                                                            }
                                                                                                                                            if (true) {
                                                                                                                                              switch(g_dst_end_week) {
                                                                                                                                              case 0x46:
                                                                                                                                                g_dst_end_week = 1;
                                                                                                                                                break;
                                                                                                                                              default:
                                                                                                                                                goto switchD_20012400_caseD_47;
                                                                                                                                              case 0x4c:
                                                                                                                                                g_dst_end_week = 5;
                                                                                                                                                break;
                                                                                                                                              case 0x51:
                                                                                                                                                g_dst_end_week = 4;
                                                                                                                                                break;
                                                                                                                                              case 0x53:
                                                                                                                                                g_dst_end_week = 2;
                                                                                                                                                break;
                                                                                                                                              case 0x54:
                                                                                                                                                g_dst_end_week = 3;
                                                                                                                                              }
                                                                                                                                              g_dst_valid_marker = 0x31121955;
                                                                                                                                              FUN_2000f82c();
                                                                                                                                              FUN_2000f28c();
                                                                                                                                              uVar14 = g_sequence_flags;
                                                                                                                                            }
                                                                                                                                          }
                                                                                                                                        }
                                                                                                                                      }
                                                                                                                                    }
                                                                                                                                  }
                                                                                                                                  else {
                                                                                                                                    cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                                                    if (local_24 < 0x19) {
                                                                                                                                      local_24 = 0x19;
                                                                                                                                    }
                                                                                                                                    else if (0x62 < local_24) {
                                                                                                                                      local_24 = 0x62;
                                                                                                                                    }
                                                                                                                                    g_cap_brightness = local_24;
                                                                                                                                    uVar14 = g_sequence_flags;
                                                                                                                                  }
                                                                                                                                }
                                                                                                                                else {
                                                                                                                                  cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                                                  if (local_24 < 0x19) {
                                                                                                                                    local_24 = 0x19;
                                                                                                                                  }
                                                                                                                                  else if (0x62 < local_24) {
                                                                                                                                    local_24 = 0x62;
                                                                                                                                  }
                                                                                                                                  g_max_brightness = local_24;
                                                                                                                                  uVar14 = g_sequence_flags;
                                                                                                                                }
                                                                                                                              }
                                                                                                                              else {
                                                                                                                                cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                                                if (local_24 == 0) {
                                                                                                                                  local_24 = 1;
                                                                                                                                }
                                                                                                                                else if (0x1e < local_24) {
                                                                                                                                  local_24 = 0x14;
                                                                                                                                }
                                                                                                                                g_min_brightness = local_24;
                                                                                                                                uVar14 = g_sequence_flags;
                                                                                                                              }
                                                                                                                            }
                                                                                                                            else {
                                                                                                                              cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                                              if (local_24 < 5) {
                                                                                                                                local_24 = 5;
                                                                                                                              }
                                                                                                                              else if (0x7f < local_24) {
                                                                                                                                local_24 = 0x7f;
                                                                                                                              }
                                                                                                                              g_max_adc = local_24;
                                                                                                                              uVar14 = g_sequence_flags;
                                                                                                                            }
                                                                                                                          }
                                                                                                                          else {
                                                                                                                            cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                                            if (local_24 == 0) {
                                                                                                                              local_24 = 1;
                                                                                                                            }
                                                                                                                            else if (0x3c < local_24) {
                                                                                                                              local_24 = 0x3c;
                                                                                                                            }
                                                                                                                            g_pin_lock = local_24;
                                                                                                                            uVar14 = g_sequence_flags;
                                                                                                                          }
                                                                                                                        }
                                                                                                                        else {
                                                                                                                          cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                                          if (local_24 == 0) {
                                                                                                                            local_24 = 1;
                                                                                                                          }
                                                                                                                          else if (0xf < local_24) {
                                                                                                                            local_24 = 0xf;
                                                                                                                          }
                                                                                                                          g_maint_time = local_24;
                                                                                                                          uVar14 = g_sequence_flags;
                                                                                                                        }
                                                                                                                      }
                                                                                                                      else {
                                                                                                                        pbVar7 = cfg_parse_base10(pcVar6,(int *)&
                                                                                                                          local_24);
                                                                                                                        if (999 < local_24) {
                                                                                                                          local_24 = 1000;
                                                                                                                        }
                                                                                                                        g_speed_a = local_24 / 10;
                                                                                                                        g_speed_b = g_speed_a;
                                                                                                                        uVar14 = g_sequence_flags;
                                                                                                                        if (*pbVar7 == 0x2c) {
                                                                                                                          cfg_parse_base10((char *)(pbVar7 + 1),
                                                                                                                           (int *)&local_24);
                                                                                                                          if (999 < local_24) {
                                                                                                                            local_24 = 1000;
                                                                                                                          }
                                                                                                                          g_speed_b = local_24 / 10;
                                                                                                                          uVar14 = g_sequence_flags;
                                                                                                                        }
                                                                                                                      }
                                                                                                                    }
                                                                                                                    else {
                                                                                                                      cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                                      if (local_24 == 0) {
                                                                                                                        local_24 = 1;
                                                                                                                      }
                                                                                                                      else if (0x5a < local_24) {
                                                                                                                        local_24 = 0x5a;
                                                                                                                      }
                                                                                                                      g_msg_timeout_ms = local_24 * 1000;
                                                                                                                      uVar14 = g_sequence_flags;
                                                                                                                    }
                                                                                                                  }
                                                                                                                  else {
                                                                                                                    cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                                    if (99 < local_24) {
                                                                                                                      local_24 = 99;
                                                                                                                    }
                                                                                                                    g_fx_slowdown = local_24;
                                                                                                                    uVar14 = g_sequence_flags;
                                                                                                                  }
                                                                                                                }
                                                                                                              }
                                                                                                              else {
                                                                                                                DAT_200238e4 = (uint)((*pbVar7 & 0x5f) == 0x59);
                                                                                                                uVar14 = g_sequence_flags;
                                                                                                              }
                                                                                                            }
                                                                                                            else {
                                                                                                              uVar14 = g_sequence_flags;
                                                                                                              if ((*pbVar7 & 0x5f) == 0x4e) {
                                                                                                                conf_swap = conf_swap & 0xfffffffe;
                                                                                                              }
                                                                                                              else if ((*pbVar7 & 0x5f) == 0x59) {
                                                                                                                conf_swap = conf_swap | 1;
                                                                                                              }
                                                                                                            }
                                                                                                          }
                                                                                                          else {
                                                                                                            cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                            uVar14 = g_sequence_flags;
                                                                                                          }
                                                                                                        }
                                                                                                        else {
                                                                                                          cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                          if (9 < local_24) {
                                                                                                            local_24 = 9;
                                                                                                          }
                                                                                                          g_flash = local_24;
                                                                                                          uVar14 = g_sequence_flags;
                                                                                                        }
                                                                                                      }
                                                                                                      else {
                                                                                                        cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                        if (local_24 < 0x32) {
                                                                                                          local_24 = 0x32;
                                                                                                        }
                                                                                                        else if (0xa0 < local_24) {
                                                                                                          local_24 = 0xa0;
                                                                                                        }
                                                                                                        g_bright_clock_ctrl =
                                                                                                        division(0x8ca00,local_24 * g_rows_per_line
                                                                                                         );
                                                                                                        uVar14 = g_sequence_flags;
                                                                                                      }
                                                                                                    }
                                                                                                    else {
                                                                                                      cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                      if (local_24 < 7) {
                                                                                                        local_24 = 7;
                                                                                                      }
                                                                                                      else if (9 < local_24) {
                                                                                                        local_24 = 9;
                                                                                                      }
                                                                                                      g_rows_per_line = local_24;
                                                                                                      uVar14 = g_sequence_flags;
                                                                                                    }
                                                                                                  }
                                                                                                  else {
                                                                                                    cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                    if (local_24 == 0) {
                                                                                                      local_24 = 1;
                                                                                                    }
                                                                                                    else if (3 < local_24) {
                                                                                                      local_24 = 3;
                                                                                                    }
                                                                                                    g_colours = local_24;
                                                                                                    uVar14 = g_sequence_flags;
                                                                                                  }
                                                                                                }
                                                                                                else {
                                                                                                  cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                  if (local_24 == 0) {
                                                                                                    local_24 = 1;
                                                                                                  }
                                                                                                  else if (8 < local_24) {
                                                                                                    local_24 = 8;
                                                                                                  }
                                                                                                  g_channels = local_24;
                                                                                                  uVar14 = g_sequence_flags;
                                                                                                }
                                                                                              }
                                                                                              else {
                                                                                                cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                                g_pixels = local_24;
                                                                                                conf_pix_count = local_24;
                                                                                                uVar14 = g_sequence_flags;
                                                                                              }
                                                                                            }
                                                                                            else {
                                                                                              uVar14 = g_sequence_flags;
                                                                                              if ((*pbVar7 & 0x5f) == 0x44) {
                                                                                                g_drive_mode_do = 0x44;
                                                                                              }
                                                                                              else if ((*pbVar7 & 0x5f) == 0x4f) {
                                                                                                g_drive_mode_do = 0x4f;
                                                                                              }
                                                                                            }
                                                                                          }
                                                                                          else {
                                                                                            cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                            if (local_24 == 0) {
                                                                                              local_24 = 1;
                                                                                            }
                                                                                            else if (200 < local_24) {
                                                                                              local_24 = 200;
                                                                                            }
                                                                                            g_speed_div_db = local_24;
                                                                                            uVar14 = g_sequence_flags;
                                                                                          }
                                                                                        }
                                                                                        else {
                                                                                          cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                          if (local_24 == 0) {
                                                                                            local_24 = 1;
                                                                                          }
                                                                                          else if (0x13 < local_24) {
                                                                                            local_24 = 0x13;
                                                                                          }
                                                                                          g_speed_div_mb = local_24;
                                                                                          uVar14 = g_sequence_flags;
                                                                                        }
                                                                                      }
                                                                                      else {
                                                                                        cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                        if (local_24 == 0) {
                                                                                          local_24 = 1;
                                                                                        }
                                                                                        else if (0x13 < local_24) {
                                                                                          local_24 = 0x13;
                                                                                        }
                                                                                        g_speed_div_d = local_24;
                                                                                        uVar14 = g_sequence_flags;
                                                                                      }
                                                                                    }
                                                                                    else {
                                                                                      cfg_parse_base10(pcVar6,(int *)&local_24);
                                                                                      if (local_24 == 0) {
                                                                                        local_24 = 1;
                                                                                      }
                                                                                      else if (0x13 < local_24) {
                                                                                        local_24 = 0x13;
                                                                                      }
                                                                                      g_speed_div_m = local_24;
                                                                                      uVar14 = g_sequence_flags;
                                                                                    }
                                                                                  }
                                                                                  else {
                                                                                    bVar5 = *pbVar7 & 0x5f;
                                                                                    uVar14 = g_sequence_flags;
                                                                                    if (bVar5 == 0x4d) {
                                                                                      g_drive_type._0_1_ = 'M';
                                                                                    }
                                                                                    else if (bVar5 == 0x54) {
                                                                                      g_drive_type._0_1_ = 'T';
                                                                                    }
                                                                                    else if (bVar5 == 0x44) {
                                                                                      g_drive_type._0_1_ = 'D';
                                                                                    }
                                                                                  }
                                                                                }
                                                                                else {
                                                                                  uVar14 = g_sequence_flags;
                                                                                  if ((*pbVar7 & 0x5f) == 0x4e) {
                                                                                    g_mode_change_clears = 0;
                                                                                  }
                                                                                  else if ((*pbVar7 & 0x5f) == 0x59) {
                                                                                    g_mode_change_clears = 1;
                                                                                  }
                                                                                }
                                                                              }
                                                                              else {
                                                                                uVar14 = g_sequence_flags;
                                                                                if ((*pbVar7 & 0x5f) == 0x4e) {
                                                                                  g_scroll_if_too_wide = 0;
                                                                                }
                                                                                else if ((*pbVar7 & 0x5f) == 0x59) {
                                                                                  g_scroll_if_too_wide = 1;
                                                                                }
                                                                              }
                                                                            }
                                                                            else {
                                                                              uVar14 = g_sequence_flags;
                                                                              if ((*pbVar7 & 0x5f) == 0x4e) {
                                                                                fpga_flags = fpga_flags & 0xfffffff0;
                                                                              }
                                                                              else if ((*pbVar7 & 0x5f) == 0x59) {
                                                                                if (pbVar7[1] == 0x2c) {
                                                                                  local_24 = pbVar7[2] - 0x30;
                                                                                  if (2 < pbVar7[2] - 0x31) {
                                                                                    local_24 = 1;
                                                                                  }
                                                                                  fpga_flags = local_24 | fpga_flags;
                                                                                }
                                                                                else {
                                                                                  fpga_flags = fpga_flags | 1;
                                                                                }
                                                                              }
                                                                            }
                                                                          }
                                                                          else {
                                                                            do {
                                                                              iVar16 = FUN_2000d05c(pbVar7,(int *)&local_24)
                                                                              ;
                                                                              pcVar6 = (char *)FUN_2000d05c((byte *)(iVar16
                                                                                + 1),(int *)&local_28);
                                                                              (&g_char_remap)[local_24] = (char)local_28;
                                                                              pbVar7 = (byte *)(pcVar6 + 1);
                                                                              uVar14 = g_sequence_flags;
                                                                            } while (*pcVar6 != '-');
                                                                          }
                                                                        }
                                                                        else {
                                                                          g_doublesided = (uint)((*pbVar7 & 0x5f) == 0x59)
                                                                          ;
                                                                          uVar14 = g_sequence_flags;
                                                                        }
                                                                      }
                                                                      else {
                                                                        g_swap_char = *pcVar6;
                                                                        uVar14 = g_sequence_flags;
                                                                      }
                                                                    }
                                                                    else {
                                                                      local_28 = 0;
                                                                      do {
                                                                        (&g_lines_per_channel)[local_28] = 1;
                                                                        local_28 = local_28 + 1;
                                                                      } while (local_28 < 8);
                                                                      local_28 = 0;
                                                                      do {
                                                                        pbVar9 = cfg_parse_base10((char *)pbVar7,
                                                                          (int *)&local_24);
                                                                        (&g_lines_per_channel)[local_28] = local_24;
                                                                        pbVar7 = pbVar9 + 1;
                                                                        uVar14 = g_sequence_flags;
                                                                        if (*pbVar9 != 0x2c) break;
                                                                        local_28 = local_28 + 1;
                                                                      } while (local_28 < 8);
                                                                    }
                                                                  }
                                                                  else {
                                                                    local_28 = 0;
                                                                    do {
                                                                      pbVar9 = cfg_parse_base10((char *)pbVar7,
                                                                        (int *)&local_24);
                                                                      (&g_missing_leds)[local_28] = local_24;
                                                                      pbVar7 = pbVar9 + 1;
                                                                      uVar14 = g_sequence_flags;
                                                                      if (*pbVar9 != 0x2c) break;
                                                                      local_28 = local_28 + 1;
                                                                    } while (local_28 < 8);
                                                                  }
                                                                }
                                                                else {
                                                                  local_28 = 0;
                                                                  do {
                                                                    (&g_channel_lengths)[local_28] = 0;
                                                                    local_28 = local_28 + 1;
                                                                  } while (local_28 < 8);
                                                                  local_28 = 0;
                                                                  do {
                                                                    pbVar9 = cfg_parse_base10((char *)pbVar7,
                                                                      (int *)&local_24);
                                                                    (&g_channel_lengths)[local_28] = local_24;
                                                                    pbVar7 = pbVar9 + 1;
                                                                    if (*pbVar9 != 0x2c) break;
                                                                    local_28 = local_28 + 1;
                                                                  } while (local_28 < 8);
                                                                  bVar2 = true;
                                                                  uVar14 = g_sequence_flags;
                                                                }
                                                              }
                                                              else {
                                                                uVar14 = g_sequence_flags;
                                                                if ((*pbVar7 & 0x5f) == 0x4e) {
                                                                  g_suppress_mon_zero = 0;
                                                                }
                                                                else if ((*pbVar7 & 0x5f) == 0x59) {
                                                                  g_suppress_mon_zero = 1;
                                                                }
                                                              }
                                                            }
                                                            else {
                                                              uVar14 = g_sequence_flags;
                                                              if ((*pbVar7 & 0x5f) == 0x4e) {
                                                                g_replace_hours_zero = 0;
                                                              }
                                                              else if ((*pbVar7 & 0x5f) == 0x59) {
                                                                g_replace_hours_zero = 1;
                                                              }
                                                            }
                                                          }
                                                          else {
                                                            uVar14 = g_sequence_flags;
                                                            if ((*pbVar7 & 0x5f) == 0x4e) {
                                                              g_suppress_day_zero = 0;
                                                            }
                                                            else if ((*pbVar7 & 0x5f) == 0x59) {
                                                              g_suppress_day_zero = 1;
                                                            }
                                                          }
                                                        }
                                                        else {
                                                          uVar14 = g_sequence_flags;
                                                          if ((*pbVar7 & 0x5f) == 0x4e) {
                                                            g_suppress_sec_zero = 0;
                                                          }
                                                          else if ((*pbVar7 & 0x5f) == 0x59) {
                                                            g_suppress_sec_zero = 1;
                                                          }
                                                        }
                                                      }
                                                      else {
                                                        uVar14 = g_sequence_flags;
                                                        if ((*pbVar7 & 0x5f) == 0x4e) {
                                                          g_suppress_min_zero = 0;
                                                        }
                                                        else if ((*pbVar7 & 0x5f) == 0x59) {
                                                          g_suppress_min_zero = 1;
                                                        }
                                                      }
                                                    }
                                                    else {
                                                      uVar14 = g_sequence_flags;
                                                      if ((*pbVar7 & 0x5f) == 0x4e) {
                                                        g_suppress_hour_zero = 0;
                                                      }
                                                      else if ((*pbVar7 & 0x5f) == 0x59) {
                                                        g_suppress_hour_zero = 1;
                                                      }
                                                    }
                                                  }
                                                  else {
                                                    uVar14 = g_sequence_flags;
                                                    if (!bVar1) {
                                                      if ((*pbVar7 & 0x5f) == 0x4e) {
                                                        g_msg_mode = 2;
                                                      }
                                                      else if ((*pbVar7 & 0x5f) == 0x59) {
                                                        g_msg_mode = 3;
                                                        bVar1 = true;
                                                      }
                                                    }
                                                  }
                                                }
                                                else {
                                                  uVar14 = g_sequence_flags;
                                                  if (!bVar1) {
                                                    if ((*pbVar7 & 0x5f) == 0x4e) {
                                                      g_msg_mode = 1;
                                                    }
                                                    else if ((*pbVar7 & 0x5f) == 0x59) {
                                                      g_msg_mode = 2;
                                                      bVar1 = true;
                                                    }
                                                  }
                                                }
                                              }
                                              else {
                                                uVar14 = g_sequence_flags;
                                                if (!bVar1) {
                                                  if ((*pbVar7 & 0x5f) == 0x4e) {
                                                    g_msg_mode = 2;
                                                  }
                                                  else if ((*pbVar7 & 0x5f) == 0x59) {
                                                    bVar1 = true;
                                                    g_msg_mode = 1;
                                                  }
                                                }
                                              }
                                            }
                                            else {
                                              FUN_2000d05c(pbVar7,(int *)&local_24);
                                              g_ddx_fixed_line = local_24;
                                              uVar14 = g_sequence_flags;
                                              if (0xf < local_24) {
                                                g_ddx_fixed_line = 0;
                                              }
                                            }
                                          }
                                          else {
                                            FUN_2000d05c(pbVar7,(int *)&local_24);
                                            g_ddx_modal_page = local_24;
                                            uVar14 = g_sequence_flags;
                                            if (0xf < local_24) {
                                              g_ddx_modal_page = 0;
                                            }
                                          }
                                          goto switchD_20012400_caseD_47;
                                        }
                                        uVar14 = g_sequence_flags;
                                        if (true) {
                                          switch(*pcVar6) {
                                          case 'R':
                                            g_current_mode = 0x52;
                                            goto switchD_20012400_caseD_47;
                                          case 'U':
                                            g_current_mode = 0x55;
                                            goto switchD_20012400_caseD_47;
                                          case 'V':
                                            g_current_mode = 0x56;
                                            goto switchD_20012400_caseD_47;
                                          case 'r':
                                            g_current_mode = 0x72;
                                            goto switchD_20012400_caseD_47;
                                          case 'u':
                                            g_current_mode = 0x75;
                                            goto switchD_20012400_caseD_47;
                                          case 'v':
                                            g_current_mode = 0x76;
                                            goto switchD_20012400_caseD_47;
                                          }
                                        }
                                        g_current_mode = 0x49;
                                        goto switchD_20012400_caseD_47;
                                      }
                                      uVar14 = g_sequence_flags;
                                      if (*pcVar6 != '1') {
                                        usart_flip = 2;
                                      }
                                    }
                                    else {
                                      uVar14 = g_sequence_flags;
                                      if ((*pbVar7 & 0x5f) == 0x4e) {
                                        g_master_mode = 0;
                                      }
                                      else if ((*pbVar7 & 0x5f) == 0x59) {
                                        g_master_mode = 1;
                                      }
                                    }
                                  }
                                  else {
                                    uVar14 = g_sequence_flags;
                                    if ((*pbVar7 & 0x5f) == 0x4e) {
                                      g_translate_arabic = 0;
                                    }
                                    else if ((*pbVar7 & 0x5f) == 0x59) {
                                      g_translate_arabic = 1;
                                    }
                                  }
                                }
                                else {
                                  uVar14 = g_sequence_flags;
                                  if ((*pbVar7 & 0x5f) == 0x4e) {
                                    g_auto_detect_arabic = 0;
                                  }
                                  else if ((*pbVar7 & 0x5f) == 0x59) {
                                    g_auto_detect_arabic = 1;
                                  }
                                }
                              }
                              else {
                                uVar14 = g_sequence_flags;
                                if ((*pbVar7 & 0x5f) == 0x4e) {
                                  g_fixed_content_def_mode = 0;
                                }
                                else if ((*pbVar7 & 0x5f) == 0x59) {
                                  g_fixed_content_def_mode = 1;
                                }
                              }
                            }
                            else {
                              if (false) {
                                switchD_20010c14_caseD_3a:
                                g_dlmx = 1;
                              }
                              else {
                                switch(pcVar6[1]) {
                                case '0':
                                  g_dlmx = 0;
                                  break;
                                case '1':
                                  g_dlmx = 1;
                                  break;
                                case '2':
                                  g_dlmx = 2;
                                  break;
                                case '3':
                                  g_dlmx = 3;
                                  break;
                                case '4':
                                  g_dlmx = 4;
                                  break;
                                case '5':
                                  g_dlmx = 5;
                                  break;
                                case '6':
                                  g_dlmx = 6;
                                  break;
                                case '7':
                                  g_dlmx = 7;
                                  break;
                                case '8':
                                  g_dlmx = 8;
                                  break;
                                case '9':
                                  g_dlmx = 9;
                                  break;
                                default:
                                  goto switchD_20010c14_caseD_3a;
                                case 'A':
                                  g_dlmx = 10;
                                  break;
                                case 'B':
                                  g_dlmx = 0xb;
                                  break;
                                case 'C':
                                  g_dlmx = 0xc;
                                  break;
                                case 'D':
                                  g_dlmx = 0xd;
                                  break;
                                case 'E':
                                  g_dlmx = 0xe;
                                  break;
                                case 'F':
                                  g_dlmx = 0xf;
                                }
                              }
                              g_dlmx_mirror = g_dlmx;
                              uVar14 = g_sequence_flags;
                            }
                            goto switchD_20012400_caseD_47;
                          }
                          switch(pcVar6[1]) {
                          case 'A':
                            local_24 = 10;
                            break;
                          case 'B':
                            local_24 = 0xb;
                            break;
                          case 'C':
                            local_24 = 0xc;
                            break;
                          case 'D':
                            local_24 = 0xd;
                            break;
                          case 'E':
                            local_24 = 0xe;
                            break;
                          case 'F':
                            local_24 = 0xf;
                            break;
                          default:
                            atoi(pcVar6 + 1,&local_24);
                            uVar14 = g_sequence_flags;
                            if ((9 < local_24) || (local_24 == 0)) goto switchD_20012400_caseD_47;
                          }
                          uVar14 = local_24;
                          g_zone_count = g_zone_count + 1;
                          pdVar10 = pdVar11;
                          while (dVar4 = *pdVar10, (char)dVar4 != '*') {
                            pdVar10 = (dword *)((int)pdVar10 + 1);
                            if (true) {
                              switch((char)dVar4) {
                              case 'h':
                                pdVar10 = (dword *)cfg_parse_base10((char *)pdVar10,
                                  (int *)&local_24);
                                (&g_zone_h)[(uVar14 * 0x29 + iVar18) * 4] = local_24;
                                break;
                              case 'l':
                                pdVar10 = (dword *)cfg_parse_base10((char *)pdVar10,
                                  (int *)&local_24);
                                iVar18 = local_24 - 1;
                                break;
                              case 'w':
                                pdVar10 = (dword *)cfg_parse_base10((char *)pdVar10,
                                  (int *)&local_24);
                                (&g_zone_w)[(uVar14 * 0x29 + iVar18) * 4] = local_24;
                                break;
                              case 'x':
                                pdVar10 = (dword *)cfg_parse_base10((char *)pdVar10,
                                  (int *)&local_24);
                                (&g_zone_x)[(uVar14 * 0x29 + iVar18) * 4] = local_24;
                                break;
                              case 'y':
                                pdVar10 = (dword *)cfg_parse_base10((char *)pdVar10,
                                  (int *)&local_24);
                                (&g_zone_y)[(uVar14 * 0x29 + iVar18) * 4] = local_24;
                              }
                            }
                          }
                          (&g_zone_line_count)[uVar14] = iVar18 + 1;
                          uVar14 = g_sequence_flags;
                          goto switchD_20012400_caseD_47;
                        }
                        atoi(pcVar6,&g_def_seq_effect);
                        twi_string_set(pcVar6);
                        uVar14 = g_sequence_flags;
                      }
                      else {
                        pbVar7 = cfg_parse_base10(pcVar6,(int *)&local_24);
                        g_canvas_x_off = local_24;
                        pbVar7 = cfg_parse_base10((char *)(pbVar7 + 1),(int *)&local_24);
                        g_canvas_y_off = local_24;
                        pbVar7 = cfg_parse_base10((char *)(pbVar7 + 1),(int *)&local_24);
                        g_canvas_height = local_24;
                        cfg_parse_base10((char *)(pbVar7 + 1),(int *)&local_24);
                        g_canvas_width = local_24;
                        bVar3 = true;
                        uVar14 = g_sequence_flags;
                      }
                    }
                    else {
                      cVar17 = *pcVar6;
                      if (cVar17 == '2') {
                        cfg_parse_base10(pcVar6 + 2,(int *)&local_24);
                        _9600 = local_24;
                        uVar14 = g_sequence_flags;
                      }
                      else if (cVar17 == '3') {
                        cfg_parse_base10(pcVar6 + 2,(int *)&local_24);
                        _9600 = local_24;
                        uVar14 = g_sequence_flags;
                      }
                      else {
                        uVar14 = g_sequence_flags;
                        if (cVar17 == '1') {
                          cfg_parse_base10(pcVar6 + 2,(int *)&local_24);
                          _19200 = local_24;
                          uVar14 = g_sequence_flags;
                        }
                      }
                    }
                  }
                  else {
                    g_fixed_width_font_flag = (uint)((*pbVar7 & 0x5f) != 0x4e);
                    uVar14 = g_sequence_flags;
                  }
                  goto switchD_20012400_caseD_47;
                }
                bVar5 = *pbVar7;
                if (bVar5 == 0x59) {
                  LAB_20010738:
                  uVar14 = g_sequence_flags | 1;
                  if (pbVar7[1] == 0x2c) {
                    pbVar9 = pbVar7 + 2;
                    bVar5 = pbVar7[2];
                    if (bVar5 == 0x59) {
                      LAB_20010788:
                      pbVar9 = pbVar7 + 3;
                      uVar14 = g_sequence_flags | 3;
                    }
                    else if (bVar5 < 0x5a) {
                      if (bVar5 == 0x4e) {
                        LAB_2001079c:
                        pbVar9 = pbVar7 + 3;
                        uVar14 = g_sequence_flags & 0xfffffffd | 1;
                      }
                    }
                    else {
                      if (bVar5 == 0x6e) goto LAB_2001079c;
                      if (bVar5 == 0x79) goto LAB_20010788;
                    }
                    g_sequence_flags = uVar14;
                    uVar14 = g_sequence_flags;
                    if (*pbVar9 == 0x2c) {
                      bVar5 = pbVar9[1];
                      if (bVar5 == 0x59) {
                        LAB_200107e4:
                        uVar14 = g_sequence_flags | 4;
                        goto switchD_20012400_caseD_47;
                      }
                      if (bVar5 < 0x5a) {
                        if (bVar5 != 0x4e) goto switchD_20012400_caseD_47;
                      }
                      else if (bVar5 != 0x6e) {
                        if (bVar5 == 0x79) goto LAB_200107e4;
                        goto switchD_20012400_caseD_47;
                      }
                      uVar14 = g_sequence_flags & 0xfffffffb;
                    }
                  }
                  goto switchD_20012400_caseD_47;
                }
                uVar14 = g_sequence_flags;
                if (bVar5 < 0x5a) {
                  if (bVar5 != 0x4e) goto switchD_20012400_caseD_47;
                }
                else if (bVar5 != 0x6e) {
                  if (bVar5 == 0x79) goto LAB_20010738;
                  goto switchD_20012400_caseD_47;
                }
                g_sequence_flags = 0;
                uVar14 = g_sequence_flags;
                goto switchD_20012400_caseD_47;
              }
              pbVar7 = cfg_parse_base10(pcVar6,(int *)&local_24);
              g_list_edit_enable = local_24;
              uVar14 = g_sequence_flags;
              if (*pbVar7 == 0x2c) {
                cfg_parse_base10((char *)pbVar7,(int *)&local_24);
                g_list_edit_value = local_24;
                uVar14 = g_sequence_flags;
              }
            }
            else {
              pbVar7 = cfg_parse_base10(pcVar6,(int *)&local_24);
              local_28 = local_24;
              uVar14 = g_sequence_flags;
              if (((*pbVar7 == 0x2c) &&
                (cfg_parse_base10((char *)(pbVar7 + 1),(int *)&local_24),
                  uVar14 = g_sequence_flags, local_24 != 0)) && (local_28 < 0x14)) {
                g_some_array_4x20[local_28] = local_24;
              uVar14 = g_sequence_flags;
            }
          }
        }
        else {
          cfg_parse_base10(pcVar6,&g_def_seq_effect);
          uVar14 = g_sequence_flags;
        }
      }
      else {
        g_zi_enable = (uint)(*pcVar6 == 'Y');
        uVar14 = g_sequence_flags;
      }
    }
    else {
      uVar14 = g_sequence_flags;
      if (*pcVar6 == 'N') {
        g_next_bus_ddx = 0;
      }
      else if (*pcVar6 == 'Y') {
        g_next_bus_ddx = 1;
        g_master_mode = 0;
      }
    }
  }
  else {
    cVar17 = *pcVar6;
    if (cVar17 == '\0' || cVar17 == ' ') {
      iVar16 = 0;
    }
    else {
      iVar16 = 0;
      do {
        (&g_device_name)[iVar16] = cVar17;
        iVar16 = iVar16 + 1;
        cVar17 = pcVar6[iVar16];
        if (cVar17 == '\0' || cVar17 == ' ') break;
      } while (iVar16 != 0x1f);
    }
    (&g_device_name)[iVar16] = 0;
    uVar14 = g_sequence_flags;
  }
  goto switchD_20012400_caseD_47;
}
pbVar7 = cfg_parse_base10(pcVar6,(int *)&local_24);
local_28 = local_24;
uVar14 = g_sequence_flags;
} while (*pbVar7 != 0x2c);
cfg_parse_base10((char *)(pbVar7 + 1),(int *)&local_24);
uVar14 = g_sequence_flags;
if (local_24 != 0x4b00) {
  if (local_24 < 0x4b01) {
    if (local_24 != 0x2580) goto switchD_20012400_caseD_47;
  }
  else if ((local_24 != 0xe100) && (local_24 != 0x1c200)) goto switchD_20012400_caseD_47;
}
if (local_28 == 1) {
  g_uart_baud_port1 = local_24;
}
else if (local_28 == 2) {
  g_uart_baud_port2 = local_24;
}
goto switchD_20012400_caseD_47;
}

