
/* WARNING: Type propagation algorithm not settling */

void command_parse(struct_msg_payload *param_1)

{
  enum_hw_flags value;
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  enum_cmd eVar5;
  char *pcVar6;
  undefined *puVar7;
  struct_cmd_buf *psVar8;
  struct_cmd_buf *psVar9;
  byte *pbVar10;
  uint uVar11;
  struct_TWI_data *psVar12;
  char *pcVar13;
  dword dVar14;
  char cVar15;
  byte bVar16;
  byte *pbVar17;
  char *pcVar18;
  struct_zone_line *psVar19;
  uint uVar20;
  bool bVar21;
  undefined1 *puVar22;
  uint uVar23;
  bool bVar24;
  bool bVar25;
  char *local_4048;
  struct_cmd_buf local_4040 [1365];
  undefined1 local_3d [9];
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;

  g_geometry_mode = 0;
  if ((param_1->flags & protocol) == 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = 2;
  }
  cmd_flags = 0;
  reply_msg = reply_tx_buf;
  reply_tx_buf[0] = '\0';
  DAT_201746ac = 0;
  if (g_zi_enable != 0) {
    pcVar18 = param_1->payload;
    iVar3 = strlen(pcVar18);
    iVar4 = strlen(s_!Zi_2002278c);
    pcVar18 = FUN_20013b50(pcVar18,iVar3,s_!Zi_2002278c,iVar4);
    if (pcVar18 != (char *)0x0) {
      clear_current_message();
      bVar21 = true;
      goto LAB_2001c610;
    }
  }
  bVar21 = false;
LAB_2001c610:
  local_4048 = (char *)0x0;
  do {
    while( true ) {
      pcVar18 = param_1->payload;
      if ((*pcVar18 == '\0') || ((char *)param_1->len <= local_4048)) {
        if (!bVar21) {
          cmd_flags = cmd_flags | 4;
        }
        finalize_active_line();
        return;
      }
      if (param_1 == (struct_msg_payload *)0x0) {
        return;
      }
      if (cmd_flags != 0) {
        return;
      }
      eVar5 = command_str_to_opcode(pcVar18);
      pcVar6 = local_4040[0].ptr;
      if (eVar5 != 0) break;
      param_1->payload = param_1->payload + 1;
    }
    pcVar13 = param_1->payload;
    cVar15 = *pcVar13;
    while (cVar15 == ' ') {
      pcVar13 = pcVar13 + 1;
      param_1->payload = pcVar13;
      cVar15 = *pcVar13;
    }
    pbVar17 = (byte *)(pcVar13 + 3);
    param_1->payload = (char *)pbVar17;
    value = hw_flags;
    uVar11 = some_line_number;
    if ((uVar2 & eVar5 >> 0x10) == 0) {
      cmd_flags = 4;
      return;
    }
    if (false) {
switchD_2001c6a4_caseD_5:
      cmd_flags = 4;
    }
    else {
      switch(eVar5 & 0xffff) {
      case cmd_sa_set_address:
        pcVar6 = cmd_sa_set_address((char *)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_st_set_time:
        pbVar17 = cmd_st_set_time(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_sd_set_date:
        pbVar17 = cmd_sd_set_date(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_sb:
        uVar11 = parse_digits((char *)pbVar17,3);
        if (uVar11 == 0xffffffff) {
          cmd_flags = 2;
        }
        else if (uVar11 < 0x65) {
          pbVar17 = (byte *)(pcVar13 + 6);
          g_brightness = uVar11;
        }
        else {
          cmd_flags = 2;
        }
        param_1->payload = (char *)pbVar17;
        break;
      default:
        goto switchD_2001c6a4_caseD_5;
      case cmd_si:
        uVar11 = parse_digits((char *)pbVar17,4);
        if (uVar11 == 0xffffffff) {
          cmd_flags = 2;
        }
        else {
          g_TWI_dirty_flags = g_TWI_dirty_flags | 1;
          pbVar17 = (byte *)(pcVar13 + 7);
          DAT_20023920 = uVar11;
          TWI_data.field0_0x0 = uVar11;
        }
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_se:
        uVar11 = parse_effect_code(pbVar17);
        uVar20 = uVar11 & 0xff;
        g_current_mode = (undefined1)uVar11;
        if (((uVar20 == 0x53 || uVar20 == 0x73) || (uVar20 == 0x43)) || (uVar20 == 99)) {
          g_current_mode = 0x49;
        }
        param_1->payload = pcVar13 + 5;
        break;
      case cmd_to_set_text_overflow:
        uVar11 = *pbVar17 - 0x30;
        if (uVar11 == 4) {
          if (g_msg_mode == 1) {
            local_3d[0] = 's';
            local_3d[1] = 99;
            puVar22 = local_3d + 2;
          }
          else {
            puVar22 = local_3d;
          }
          if (g_msg_mode == 2) {
            *puVar22 = 0x74;
            puVar22[1] = 99;
            puVar22 = puVar22 + 2;
          }
          if (g_msg_mode == 3) {
            *puVar22 = 0x74;
            puVar22[1] = 0x77;
            puVar22 = puVar22 + 2;
          }
          *puVar22 = 0;
          reply_add_field(local_3d,(int)puVar22 - (int)local_3d);
        }
        else if ((uVar11 < 4) && (uVar11 != 0)) {
          g_msg_mode = uVar11;
        }
        param_1->payload = pcVar13 + 4;
        break;
      case cmd_ad_autodetect_arabic:
        g_auto_detect_arabic = (uint)(*pbVar17 == 0x79 || *pbVar17 == 0x59);
        param_1->payload = pcVar13 + 4;
        break;
      case cmd_sf:
        g_master_mode = (uint)(*pbVar17 == 0x79 || *pbVar17 == 0x59);
        param_1->payload = pcVar13 + 4;
        break;
      case cmd_sg:
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        if (local_3d._5_4_ == 0xffffffff) {
          g_cap_brightness = 0xffffffff;
        }
        else {
          if ((uint)local_3d._5_4_ < g_min_brightness) {
            local_3d._5_4_ = g_min_brightness;
          }
          if (g_max_brightness < (uint)local_3d._5_4_) {
            local_3d._5_4_ = g_max_brightness;
          }
          g_cap_brightness = local_3d._5_4_;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_xM:
        local_3d._5_4_ = 0xffffffff;
        local_34 = 0xffffffff;
        if (g_list_edit_enable != 1) {
          if (*pbVar17 == 0x61) {
switchD_2001d2d4_caseD_61:
            g_list_edit_enable = 1;
            TWI_data.list_edit_enable = 1;
            g_TWI_dirty_flags = g_TWI_dirty_flags | 0x4000;
          }
          else {
            reply_add_field("NA",2);
          }
          goto LAB_2001d754;
        }
        if (false) {
switchD_2001d2d4_caseD_62:
          pbVar17 = (byte *)atoi((char *)pbVar17,(uint *)(local_3d + 5));
          uVar1 = local_3d._5_4_;
          uVar11 = cmd_xM_case_default(local_3d._5_4_);
          if (uVar11 == 0) {
LAB_2001d734:
            g_list_edit_value = uVar1;
            TWI_data.list_edit_value = uVar1;
            g_TWI_dirty_flags = g_TWI_dirty_flags | 0x4000;
          }
          else if (uVar11 < 3) {
            cmd_flags = 2;
          }
          else {
            if (uVar11 != 3) goto LAB_2001d734;
            reply_add_field("NA",2);
          }
        }
        else {
          switch(*pbVar17) {
          case 0x61:
            goto switchD_2001d2d4_caseD_61;
          default:
            goto switchD_2001d2d4_caseD_62;
          case 99:
            pbVar17 = (byte *)atoi(pcVar13 + 4,&local_34);
            if (local_34 == 0xffffffff) {
              cmd_flags = 2;
            }
            else {
              dVar14 = 0;
              do {
                if ((g_some_array_4x20[dVar14] != 0) && (local_34 == g_some_array_4x20[dVar14])) {
                  g_TWI_dirty_flags = g_TWI_dirty_flags | 0x4000;
                  g_list_edit_value = dVar14;
                  TWI_data.list_edit_value = dVar14;
                  goto LAB_2001d754;
                }
                dVar14 = dVar14 + 1;
              } while (dVar14 != 0x14);
              reply_add_field("NA",2);
            }
            break;
          case 100:
            g_list_edit_enable = 0;
            TWI_data.list_edit_enable = 0;
            g_TWI_dirty_flags = g_TWI_dirty_flags | 0x4000;
            break;
          case 0x73:
            pcVar6 = atoi(pcVar13 + 4,(uint *)(local_3d + 5));
            pbVar17 = (byte *)atoi(pcVar6 + 1,&local_34);
            if (((uint)local_3d._5_4_ < 0x14) && (local_34 != 0xffffffff)) {
              uVar11 = 0;
              do {
                if (g_some_array_4x20[uVar11] == 0) break;
                uVar11 = uVar11 + 1;
              } while (uVar11 != 0x14);
              if (uVar11 < (uint)local_3d._5_4_) {
                cmd_flags = 2;
              }
              else {
                g_some_array_4x20[local_3d._5_4_] = local_34;
                TWI_data.field33_0x100[local_3d._5_4_] = local_34;
                if ((uint)local_3d._5_4_ < 0x10) {
                  g_TWI_dirty_flags = g_TWI_dirty_flags | 0x10;
                }
                else {
                  g_TWI_dirty_flags = g_TWI_dirty_flags | 0x20;
                }
              }
            }
            else {
              cmd_flags = 2;
            }
            break;
          case 0x77:
            pbVar17 = (byte *)atoi(pcVar13 + 4,(uint *)(local_3d + 5));
            uVar1 = local_3d._5_4_;
            uVar11 = cmd_xM_case_default(local_3d._5_4_);
            if (uVar11 == 0) {
LAB_2001d68c:
              g_some_array_4x20[uVar1] = 0;
              TWI_data.field33_0x100[local_3d._5_4_] = 0xffffffff;
              if ((uint)local_3d._5_4_ < 0x10) {
                g_TWI_dirty_flags = g_TWI_dirty_flags | 0x10;
              }
              else {
                g_TWI_dirty_flags = g_TWI_dirty_flags | 0x20;
              }
            }
            else if (uVar11 < 3) {
              cmd_flags = 2;
            }
            else if (uVar11 != 3) goto LAB_2001d68c;
          }
        }
LAB_2001d754:
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_xF:
        pcVar6 = cmd_zF_handle((char *)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_up:
        pbVar17 = cmd_up_handle(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_uq_set_sequence_timer:
        iVar3 = parse_digits((char *)pbVar17,2);
        if (iVar3 == -1) {
          cmd_flags = 2;
        }
        else if (iVar3 - 1U < 0x14) {
          g_msg_timeout_ms = iVar3 * 1000;
          pbVar17 = (byte *)(pcVar13 + 5);
        }
        else {
          cmd_flags = 2;
        }
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_uf:
        uVar11 = parse_digits((char *)pbVar17,3);
        if (uVar11 == 0xffffffff) {
          cmd_flags = 2;
        }
        else {
          uVar20 = parse_digits(pcVar13 + 7,3);
          if (uVar20 == 0xffffffff) {
            cmd_flags = 2;
          }
          else if (pcVar13[6] == ',') {
            if (uVar11 == 999) {
              uVar11 = 1000;
            }
            if (uVar20 == 999) {
              uVar20 = 1000;
            }
            g_speed_a = uVar11 / 10;
            g_speed_b = uVar20 / 10;
            if (g_speed_a < 10) {
              g_speed_a = 10;
            }
            if (g_speed_b < 10) {
              g_speed_b = 10;
            }
            pbVar17 = (byte *)(pcVar13 + 10);
          }
          else {
            cmd_flags = 8;
          }
        }
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_us_uz:
        pcVar6 = (char *)cmd_us_uz_handle((int)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_rs_rz:
        pcVar6 = utoa(local_3d,2,g_fixed_font_flag);
        *pcVar6 = '\0';
        reply_add_field(local_3d,(int)pcVar6 - (int)local_3d);
        break;
      case cmd_um:
        uVar11 = parse_digits((char *)pbVar17,2);
        if (uVar11 == 0xffffffff) {
          cmd_flags = 2;
        }
        else if (uVar11 < 0x10) {
          g_TWI_dirty_flags = g_TWI_dirty_flags | 1;
          pbVar17 = (byte *)(pcVar13 + 5);
          g_maint_time = uVar11;
          TWI_data.field1_0x4 = uVar11;
        }
        else {
          cmd_flags = 2;
        }
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_ul:
        uVar11 = parse_digits((char *)pbVar17,2);
        if (uVar11 == 0xffffffff) {
          cmd_flags = 2;
        }
        else if (uVar11 < 0x3d) {
          pbVar17 = (byte *)(pcVar13 + 5);
          g_pin_lock = uVar11;
        }
        else {
          cmd_flags = 2;
        }
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_ue:
        uVar11 = parse_digits((char *)pbVar17,1);
        if (uVar11 == 0xffffffff) {
          cmd_flags = 2;
        }
        else if (uVar11 < 2) {
          g_TWI_dirty_flags = g_TWI_dirty_flags | 1;
          pbVar17 = (byte *)(pcVar13 + 4);
          DAT_2002392c = uVar11;
          TWI_data.field3_0xc = uVar11;
        }
        else {
          cmd_flags = 2;
        }
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_?p_check_presence:
        pcVar6 = utoa(local_3d,1,1);
        *pcVar6 = '\0';
        reply_add_field(local_3d,(int)pcVar6 - (int)local_3d);
        break;
      case cmd_uj:
        pcVar6 = fpga_register_update?((char *)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_uk:
        pcVar6 = atoi((char *)pbVar17,&local_34);
        if (local_34 == 0xffffffff) {
          cmd_flags = 2;
        }
        else {
          if (2 < local_34 - 1) {
            local_34 = 1;
          }
          fpga_flags = fpga_flags & 0xfffffff0 | local_34;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_ew:
        local_34 = 0xffffffff;
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        pcVar6 = atoi(pcVar6 + 1,&local_30);
        if (pcVar6[1] == 'N') {
          pcVar6 = pcVar6 + 2;
        }
        else {
          pcVar6 = atoi(pcVar6 + 1,&local_34);
        }
        if (((int)local_3d._5_4_ < 0) || ((int)local_30 < 0)) {
          cmd_flags = 2;
        }
        else {
          while (local_30 = local_30 - 1, local_30 != 0xffffffff) {
            if ((uint)local_3d._5_4_ < 0x1000) {
              (&g_TWI_dirty_flags)[(uint)local_3d._5_4_ >> 9] =
                   (&g_TWI_dirty_flags)[(uint)local_3d._5_4_ >> 9] |
                   1 << ((local_3d._5_4_ & 0x1ff) >> 4);
              TWI_data.timeout_cmd_str[local_3d._5_4_ - 0x20] = local_34;
              local_3d._5_4_ = local_3d._5_4_ + 1;
            }
          }
        }
        param_1->payload = pcVar6;
        break;
      case cmd_eb:
        local_30 = 0xff;
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        pcVar6 = atoi(pcVar6 + 1,&local_34);
        if (pcVar6[1] == 'N') {
          pcVar6 = pcVar6 + 2;
        }
        else {
          pcVar6 = atoi(pcVar6 + 1,&local_30);
        }
        if (((int)local_3d._5_4_ < 0) || ((int)local_34 < 0)) {
          cmd_flags = 2;
        }
        else {
          while (local_34 = local_34 - 1, local_34 != 0xffffffff) {
            if ((uint)local_3d._5_4_ < 0x4000) {
              (&g_TWI_dirty_flags)[(uint)local_3d._5_4_ >> 0xb] =
                   (&g_TWI_dirty_flags)[(uint)local_3d._5_4_ >> 0xb] |
                   1 << ((local_3d._5_4_ & 0x7ff) >> 6);
              *(char *)((int)TWI_data.timeout_cmd_str + (local_3d._5_4_ - 0x80)) = (char)local_30;
              local_3d._5_4_ = local_3d._5_4_ + 1;
            }
          }
        }
        param_1->payload = pcVar6;
        break;
      case cmd_es:
        pcVar6 = atoi((char *)pbVar17,&local_34);
        pcVar6 = atoi(pcVar6 + 1,(uint *)(local_3d + 5));
        pcVar6 = pcVar6 + 1;
        if (((int)local_34 < 0) || ((int)local_3d._5_4_ < 0)) {
          cmd_flags = 2;
        }
        else {
          while (local_3d._5_4_ = local_3d._5_4_ - 1, local_3d._5_4_ != 0xffffffff) {
            if (local_34 < 0x4000) {
              (&g_TWI_dirty_flags)[local_34 >> 0xb] =
                   (&g_TWI_dirty_flags)[local_34 >> 0xb] | 1 << ((local_34 & 0x7ff) >> 6);
              *(char *)((int)TWI_data.timeout_cmd_str + (local_34 - 0x80)) = *pcVar6;
              local_34 = local_34 + 1;
              pcVar6 = pcVar6 + 1;
            }
          }
        }
        param_1->payload = pcVar6;
        break;
      case cmd_ua:
        local_34 = 0;
        pcVar6 = atoi((char *)pbVar17,&local_34);
        if (local_34 == 0xffffffff) {
          cmd_flags = 2;
        }
        else {
          g_max_scrolls = local_34;
          TWI_data.max_scrolls = local_34;
          g_TWI_dirty_flags = g_TWI_dirty_flags | 0x4000;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_ub:
        local_34 = 0;
        pcVar6 = atoi((char *)pbVar17,&local_34);
        if (false) {
switchD_2001db58_caseD_2:
          cmd_flags = 2;
        }
        else {
          switch(local_34) {
          case 0:
            g_sequence_flags = 0;
            break;
          case 1:
            g_sequence_flags = 1;
            break;
          default:
            goto switchD_2001db58_caseD_2;
          case 3:
            g_sequence_flags = 3;
            break;
          case 5:
            g_sequence_flags = 5;
            break;
          case 7:
            g_sequence_flags = 7;
          }
        }
        param_1->payload = pcVar6;
        break;
      case cmd_uh:
        local_34 = 0;
        bVar16 = *pbVar17;
        pcVar6 = atoi(pcVar13 + 4,&local_34);
        if (local_34 == 0xffffffff) {
          cmd_flags = 2;
        }
        else if (bVar16 == 0x4e) {
LAB_2001daf8:
          g_led_err_min = local_34;
          TWI_data.led_err_min = local_34;
          g_TWI_dirty_flags = g_TWI_dirty_flags | 2;
        }
        else {
          if (bVar16 < 0x4f) {
            if (bVar16 != 0x43) {
LAB_2001db1c:
              cmd_flags = 2;
              goto LAB_2001db28;
            }
          }
          else if (bVar16 != 99) {
            if (bVar16 == 0x6e) goto LAB_2001daf8;
            goto LAB_2001db1c;
          }
          g_led_err_max = local_34;
          TWI_data.led_err_max = local_34;
          g_TWI_dirty_flags = g_TWI_dirty_flags | 2;
        }
LAB_2001db28:
        param_1->payload = pcVar6;
        break;
      case cmd_??_dump_config:
        build_info_string();
        break;
      case cmd_?a:
        pcVar6 = serial_number_compare_stuff((char *)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_?t:
        psVar9 = local_4040;
        bin_to_hex((char *)local_4040,2,(uint)g_rtc_hours);
        bin_to_hex((char *)psVar9,2,(uint)g_rtc_minutes);
        bin_to_hex((char *)psVar9,2,(uint)g_rtc_seconds);
        *(char *)&psVar9->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
        break;
      case cmd_?r:
        FUN_2001837c();
        break;
      case cmd_?d:
        psVar9 = local_4040;
        bin_to_hex((char *)local_4040,1,(uint)g_rtc_day_of_week);
        bin_to_hex((char *)psVar9,2,(uint)g_rtc_day_of_month);
        bin_to_hex((char *)psVar9,2,(uint)g_rtc_month);
        bin_to_hex((char *)psVar9,2,(uint)g_rtc_year);
        *(char *)&psVar9->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
        break;
      case cmd_?b:
        pcVar6 = utoa((char *)local_4040,3,current_brightness);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_?d|cmd_st_set_time:
      case cmd_ut|cmd_sa_set_address:
        break;
      case cmd_?i:
        if (DAT_20023920 < 10000) {
          psVar9 = (struct_cmd_buf *)utoa((char *)local_4040,4,DAT_20023920);
        }
        else {
          psVar9 = local_4040;
          strcpy((char *)psVar9,"----");
        }
        *(char *)&psVar9->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
        break;
      case cmd_?f:
        if (g_cap_brightness == 0xffffffff) {
          psVar9 = local_4040;
          strcpy((char *)psVar9,"No Br Cap");
        }
        else {
          psVar9 = (struct_cmd_buf *)utoa((char *)local_4040,4,g_cap_brightness);
        }
        *(char *)&psVar9->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
        break;
      case cmd_?g:
        psVar9 = local_4040;
        bin_to_hex((char *)local_4040,1,g_dlmx_mirror);
        *(char *)&psVar9->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
        break;
      case cmd_?n:
        psVar9 = local_4040;
        strcpy((char *)local_4040,&serial_number);
        *(char *)&psVar9->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
        break;
      case cmd_?v_get_version:
        puVar7 = get_app_version();
        psVar9 = local_4040;
        bin_to_hex((char *)local_4040,4,(uint)puVar7 >> 0x10);
        pcVar6 = (char *)((int)&psVar9->ptr + 1);
        *(char *)&psVar9->ptr = ',';
        bin_to_hex(pcVar6,4,(uint)puVar7 & 0xffff);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_?c_?z:
        uVar11 = 0;
        iVar3 = 0;
        uVar20 = g_colours;
        do {
          if (*(int *)((int)&g_channel_lengths + iVar3) != 0) {
            uVar11 = uVar11 + *(int *)((int)&g_lines_per_channel + iVar3);
          }
          uVar20 = uVar20 + g_colours;
          iVar3 = iVar3 + g_colours * 4;
        } while (uVar20 - g_colours < 8);
        if (g_doublesided != 0) {
          uVar11 = uVar11 >> 1;
        }
        if (g_next_bus_ddx == 0) {
          pcVar6 = utoa((char *)local_4040,4,g_pixels);
          *pcVar6 = ',';
          psVar9 = (struct_cmd_buf *)utoa(pcVar6 + 1,4,g_rows_per_line * uVar11);
        }
        else {
          DAT_201746ac = 1;
          if (g_device_name == '\0') {
            psVar8 = local_4040;
            bin_to_hex((char *)psVar8,4,g_pixels);
            psVar9 = (struct_cmd_buf *)((int)&psVar8->ptr + 1);
            *(char *)&psVar8->ptr = ',';
            bin_to_hex((char *)psVar9,4,g_rows_per_line * uVar11);
          }
          else {
            psVar9 = local_4040;
            iVar3 = 0;
            cVar15 = g_device_name;
            do {
              *(char *)((int)&local_4040[0].ptr + iVar3) = cVar15;
              psVar9 = (struct_cmd_buf *)((int)&psVar9->ptr + 1);
              cVar15 = (&DAT_2017468d)[iVar3];
              iVar3 = iVar3 + 1;
            } while (cVar15 != '\0');
          }
        }
        if (g_next_bus_ddx == 0) {
          *(char *)&psVar9->ptr = ',';
          if (g_colours < 2) {
            *(char *)((int)&psVar9->ptr + 1) = 'M';
          }
          else {
            *(char *)((int)&psVar9->ptr + 1) = 'C';
          }
          *(char *)((int)&psVar9->ptr + 2) = ',';
          if (g_doublesided == 0) {
            *(char *)((int)&psVar9->ptr + 3) = 'S';
            *(undefined1 *)&psVar9->count = 0x53;
            psVar9 = (struct_cmd_buf *)((int)&psVar9->count + 1);
          }
          else {
            *(char *)((int)&psVar9->ptr + 3) = 'D';
            *(undefined1 *)&psVar9->count = 0x44;
            psVar9 = (struct_cmd_buf *)((int)&psVar9->count + 1);
          }
        }
        *(char *)&psVar9->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
        break;
      case cmd_?j:
        FUN_2001833c();
        break;
      case cmd_?e_get_led_errors:
        if (g_detailed_diag_info_flag == 0) {
          pcVar6 = utoa((char *)local_4040,5,g_led_failures);
        }
        else {
          pcVar6 = utoa((char *)local_4040,5,0x3039);
          pcVar6 = utoa(pcVar6,5,DAT_20187638);
          pcVar6 = utoa(pcVar6,5,DAT_2018763c);
          pcVar6 = utoa(pcVar6,5,DAT_20187640);
          pcVar6 = utoa(pcVar6,5,DAT_20187644);
          pcVar6 = utoa(pcVar6,5,DAT_20187648);
          pcVar6 = utoa(pcVar6,5,DAT_2018764c);
          pcVar6 = utoa(pcVar6,5,DAT_20187650);
          pcVar6 = utoa(pcVar6,5,DAT_20187654);
        }
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_?m:
        psVar9 = local_4040;
        bin_to_hex((char *)local_4040,2,DAT_20174664);
        *(char *)&psVar9->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
        DAT_20174664 = 0;
        break;
      case cmd_?o:
        psVar9 = local_4040;
        bin_to_hex((char *)local_4040,2,DAT_20174660);
        *(char *)&psVar9->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
        DAT_20174660 = 0;
        break;
      case cmd_?h:
        DAT_200238fc = 0;
        hw_flags = 0;
        psVar9 = local_4040;
        bin_to_hex((char *)local_4040,2,value);
        *(char *)&psVar9->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
        break;
      case cmd_?l:
        if ((int)fpga_flags < 0) {
          reply_add_field("PCB294",6);
        }
        else {
          reply_add_field("PCB175",6);
        }
        break;
      case cmd_?k:
        uVar11 = fpga_flags & 0xf;
        if (uVar11 == 2) {
          reply_add_field("S",1);
        }
        else if (uVar11 == 3) {
          reply_add_field("A",1);
        }
        else if (uVar11 == 1) {
          reply_add_field("M",1);
        }
        else {
          reply_add_field("None",4);
        }
        break;
      case cmd_uc:
        pcVar6 = cmd_uc_handle((char *)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_?s_get_serial:
        utoa(local_3d,3,g_max_scrolls);
        local_3d[3] = 0;
        reply_add_field(local_3d,3);
        break;
      case cmd_?x:
        pcVar6 = cmd_Qx_handle((char *)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_rp:
        pcVar6 = utoa((char *)local_4040,2,g_fx_slowdown);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_rt:
        pcVar6 = &DAT_20189678;
        if (DAT_20023918 == 1) {
          pcVar6 = &DAT_2018df6c;
        }
        cVar15 = *pcVar6;
        if (cVar15 != '\0') {
          iVar3 = 0;
          pcVar13 = reply_msg;
          do {
            reply_msg = pcVar13 + 1;
            *pcVar13 = cVar15;
            iVar3 = iVar3 + 1;
            cVar15 = pcVar6[iVar3];
            pcVar13 = reply_msg;
          } while (cVar15 != '\0');
        }
        *reply_msg = '\0';
        reply_msg = reply_msg + 1;
        break;
      case cmd_rq:
        pcVar6 = utoa((char *)local_4040,2,g_msg_timeout_ms / 1000);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_rf:
        pcVar6 = utoa((char *)local_4040,3,g_speed_a * 10);
        *pcVar6 = ',';
        pcVar6 = utoa(pcVar6 + 1,3,g_speed_b * 10);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_rm:
        pcVar6 = utoa((char *)local_4040,2,g_maint_time);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_rl:
        pcVar6 = utoa((char *)local_4040,2,g_pin_lock);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_re:
        pcVar6 = utoa((char *)local_4040,1,DAT_2002392c);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_rb:
        pcVar6 = utoa((char *)local_4040,3,g_brightness);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_qm:
        param_1->payload = pcVar13 + 4;
        uVar11 = hex_to_bin((char *)pbVar17);
        if (uVar11 < 0x11) {
          if ((&g_zone_line_count)[uVar11] == 0) {
            psVar9 = local_4040;
            strcpy((char *)psVar9,"M_,NL");
          }
          else {
            psVar9 = local_4040;
            strcpy((char *)psVar9,"M_,\n");
          }
          uVar20 = 0;
          *(char *)&psVar9->ptr = '\0';
          bin_to_hex((char *)((int)&local_4040[0].ptr + 1),1,uVar11);
          if ((&g_zone_line_count)[uVar11] == 0) {
            reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
          }
          else {
            if (0x17 < 0x4000 - ((int)psVar9 - (int)local_4040)) {
              psVar19 = g_abZoneLines + uVar11 * 0x29;
              psVar8 = psVar9;
              do {
                psVar9 = psVar8;
                strcpy((char *)psVar8,"L__x____y___h___w____\n");
                uVar20 = uVar20 + 1;
                utoa((char *)((int)&psVar8->ptr + 1),2,uVar20);
                utoa((char *)&psVar8->count,4,psVar19->dwX);
                utoa((char *)((int)&psVar8->size + 1),3,psVar19->dwY);
                utoa((char *)((int)&psVar8[1].ptr + 1),3,psVar19->dwH);
                utoa((char *)((int)&psVar8[1].count + 1),4,psVar19->dwW);
                if ((uint)(&g_zone_line_count)[uVar11] <= uVar20) break;
                psVar19 = psVar19 + 1;
                psVar8 = psVar9;
              } while (0x17 < 0x4000 - ((int)psVar9 - (int)local_4040));
            }
            *(char *)&psVar9->ptr = '\0';
            reply_add_field((char *)local_4040,(int)psVar9 - (int)local_4040);
          }
        }
        else {
          cmd_flags = 2;
        }
        break;
      case cmd_ql:
        uVar11 = 0;
        psVar9 = local_4040;
        do {
          psVar8 = psVar9;
          if ((&g_zone_line_count)[uVar11] != 0) {
            bin_to_hex((char *)psVar9,1,uVar11);
            psVar8 = (struct_cmd_buf *)((int)&psVar9->ptr + 1);
            *(char *)&psVar9->ptr = ',';
          }
          uVar11 = uVar11 + 1;
          psVar9 = psVar8;
        } while (uVar11 != 0x10);
        if (psVar8 != local_4040) {
          psVar8 = (struct_cmd_buf *)((int)&psVar8[-1].size + 3);
        }
        *(char *)&psVar8->ptr = '\0';
        reply_add_field((char *)local_4040,(int)psVar8 - (int)local_4040);
        break;
      case cmd_qc:
        memcpy(local_3d,"_,_",4);
        iVar4 = 0;
        iVar3 = 0;
        do {
          if (*(int *)((int)&g_zone_line_count + iVar3) != 0) {
            iVar4 = iVar4 + 1;
          }
          iVar3 = iVar3 + 4;
        } while (iVar3 != 0x40);
        uVar11 = iVar4 - g_zone_count;
        bin_to_hex(local_3d,1,g_zone_count);
        bin_to_hex(local_3d + 2,1,uVar11 & ~((int)uVar11 >> 0x1f));
        reply_add_field(local_3d,3);
        break;
      case cmd_?u:
        bin_to_hex(local_3d,1,g_dlmx);
        local_3d[1] = 0;
        reply_add_field(local_3d,1);
        break;
      case cmd_qf:
        local_4040[0].ptr = (char *)0x5f5f5f5f;
        local_4040[0].count._0_1_ = '_';
        local_4040[0].count._1_1_ = '_';
        local_4040[0].count._2_1_ = '_';
        local_4040[0].count._3_1_ = '_';
        local_4040[0].size = (uint)local_4040[0].size._1_3_ << 8;
        bin_to_hex((char *)local_4040,1,g_ddx_modal_page);
        reply_add_field((char *)local_4040,1);
        break;
      case cmd_qi:
        local_4040[0].ptr = (char *)0x5f5f5f5f;
        local_4040[0].count._0_1_ = '_';
        local_4040[0].count._1_1_ = '_';
        local_4040[0].count._2_1_ = '_';
        local_4040[0].count._3_1_ = '_';
        local_4040[0].size = (uint)local_4040[0].size._1_3_ << 8;
        bin_to_hex((char *)local_4040,1,g_ddx_fixed_line);
        reply_add_field((char *)local_4040,1);
        break;
      case cmd_?q:
        if ((int)fpga_flags < 0) {
          strcpy((char *)local_4040,"MA--SA--L--%---");
          pcVar6 = (char *)((int)&local_4040[0].ptr + 2);
          bin_to_hex(pcVar6,2,DAT_2017467c);
          pcVar6 = pcVar6 + 2;
          bin_to_hex(pcVar6,2,DAT_20174680);
          pcVar6 = pcVar6 + 1;
          bin_to_hex(pcVar6,2,DAT_2018df44);
          pcVar6 = utoa(pcVar6 + 1,3,DAT_2018df48);
        }
        else {
          strcpy((char *)local_4040,"A--L--%---");
          pcVar6 = (char *)((int)&local_4040[0].ptr + 1);
          bin_to_hex(pcVar6,2,DAT_20187634);
          pcVar6 = pcVar6 + 1;
          bin_to_hex(pcVar6,2,DAT_2018df44);
          pcVar6 = utoa(pcVar6 + 1,3,DAT_2018df48);
        }
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_rc:
        pbVar17 = cmd_rc_handle(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_rh:
        pcVar6 = utoa((char *)local_4040,6,g_led_err_max);
        *pcVar6 = ',';
        pcVar6 = utoa(pcVar6 + 1,6,g_led_err_min);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_sr:
        cmd_sr_handle();
        break;
      case cmd_za_zd:
        DAT_20174670 = 0;
        DAT_20174674 = 1;
        show_default_message();
        break;
      case cmd_zp:
        pbVar17 = cmd_zp(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_zo:
        pbVar17 = cmd_zo_fpga_write(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_cp:
        pbVar17 = FUN_20017830(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_zz:
        cmd_zz_reboot_flag5((byte *)param_1);
        break;
      case cmd_zb_reboot:
        cmd_zb_reboot((byte *)param_1);
        break;
      case cmd_zr:
        cmd_zr_reboot_flag2((byte *)param_1);
        break;
      case cmd_zy:
        cmd_zy_reboot_flag3((byte *)param_1);
        break;
      case cmd_zl:
        DAT_2017471c = 0;
        break;
      case cmd_ps:
        pcVar6 = (char *)cmd_ps_page_show((int)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_pd:
        pcVar6 = (char *)cmd_pd_handle((int)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_pr:
        cmd_pr_handle();
        break;
      case cmd_pl_playlist:
        pcVar6 = cmd_page_load((char *)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_px_playlist_clear:
        cmd_px_clear_playlist();
        break;
      case cmd_ls:
        pcVar6 = (char *)cmd_line_list_select((int)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_lr:
        if ((g_current_channel == 0x69) && (some_line_number != 0xffffffff)) {
          pbVar17 = (byte *)atoi((char *)pbVar17,(uint *)(local_3d + 5));
          if (local_3d._5_4_ == 0xffffffff) {
            reply_code = 0x99;
            cmd_flags = 2;
          }
          else if (uVar11 == local_3d._5_4_) {
            DAT_2017474c = 1;
          }
          else {
            reply_code = local_3d._5_4_ << 0x10 | 0x6900009b;
            cmd_flags = 2;
          }
        }
        else {
          reply_code = local_3d._5_4_ << 0x18 | 0x9a;
          cmd_flags = 2;
        }
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_lc:
        pcVar6 = (char *)cmd_line_list_select((int)pbVar17);
        param_1->payload = pcVar6;
        DAT_20174734 = 1;
        break;
      case cmd_lp:
        if ((g_current_channel == 0x69) && (some_line_number != 0xffffffff)) {
          pbVar17 = (byte *)atoi((char *)pbVar17,(uint *)(local_3d + 5));
          if (local_3d._5_4_ == 0xffffffff) {
            reply_code = 0x9c;
            cmd_flags = 2;
          }
          else {
            DAT_20174750 = local_3d._5_4_;
          }
        }
        else {
          reply_code = 0x9c;
          cmd_flags = 2;
        }
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_lh:
        if ((g_current_channel == 0x69) && (some_line_number != 0xffffffff)) {
          pbVar17 = (byte *)atoi((char *)pbVar17,(uint *)(local_3d + 5));
          if (local_3d._5_4_ == 0xffffffff) {
            reply_code = 0x96;
            cmd_flags = 2;
          }
          else if (uVar11 == local_3d._5_4_) {
            DAT_20174754 = 1;
          }
          else {
            reply_code = local_3d._5_4_ << 0x10 | 0x69000098;
            cmd_flags = 2;
          }
        }
        else {
          reply_code = 0x96;
          cmd_flags = 2;
        }
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_lt:
        pcVar6 = cmd_lt_handle((char *)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_Fm_define_mapping:
        pbVar17 = cmd_Fm_handle(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_m0_load_mapping0:
        cmd_page_preset_select(0);
        break;
      case cmd_m1_load_mapping1:
        if (g_next_bus_ddx == 0) {
          cmd_page_preset_select(1);
        }
        else {
          cmd_page_preset_select(2);
        }
        break;
      case cmd_m2_load_mapping2:
        cmd_page_preset_select(2);
        break;
      case cmd_m3_load_mapping3:
        cmd_page_preset_select(3);
        break;
      case cmd_m4_load_mapping4:
        cmd_page_preset_select(4);
        break;
      case cmd_m5_load_mapping5:
        cmd_page_preset_select(5);
        break;
      case cmd_m6_load_mapping6:
        cmd_page_preset_select(6);
        break;
      case cmd_m7_load_mapping7:
        cmd_page_preset_select(7);
        break;
      case cmd_m8_load_mapping8:
        cmd_page_preset_select(8);
        break;
      case cmd_m9_load_mapping9:
        cmd_page_preset_select(9);
        break;
      case cmd_mA_load_mapping10:
        cmd_page_preset_select(10);
        break;
      case cmd_mB_load_mapping11:
        cmd_page_preset_select(0xb);
        break;
      case cmd_mC_load_mapping12:
        cmd_page_preset_select(0xc);
        break;
      case cmd_mD_load_mapping13:
        cmd_page_preset_select(0xd);
        break;
      case cmd_mE_load_mapping14:
        cmd_page_preset_select(0xe);
        break;
      case cmd_mF_load_mapping15:
        cmd_page_preset_select(0xf);
        break;
      case cmd_mX_mx_load_mapping:
        cmd_page_preset_select(g_dlmx_mirror);
        break;
      case cmd_cd:
        clear_current_message();
        break;
      case cmd_cl:
        pcVar6 = (char *)cmd_cl_handle((int)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_dl_define_line:
        pbVar17 = cmd_dl_define_line(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_dg_draw_graphics:
        pbVar17 = cmd_dg_draw_graphics((int)pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_df:
        pbVar17 = cmd_df_handle(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_dr:
        pbVar17 = cmd_dr_handle_increment_value(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_dp_display_pause:
        pcVar6 = (char *)cmd_dp_display_position((int)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_dw:
        cmd_dw_display_window();
        break;
      case cmd_kt_load_text:
        pbVar17 = cmd_kt_handle(pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_kg_load_graphics:
        pbVar17 = cmd_kg_handle((int)pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_kb:
        pbVar17 = (byte *)atoi((char *)pbVar17,(uint *)(local_3d + 5));
        if ((uint)local_3d._5_4_ < 0x100) {
          pbVar10 = pbVar17 + 1;
          if (*pbVar17 == 0x3c) {
            local_4040[0].ptr = g_string_format_work_buf;
            local_4040[0].count = 0;
            local_4040[0].size = 0x40;
            pbVar10 = markup_compile(pbVar10,local_4040,0);
            memcpy(g_kb_message_array + local_3d._5_4_,g_string_format_work_buf,0x40);
            DAT_20174718 = 1;
          }
          else {
            cmd_flags = 8;
          }
        }
        else {
          cmd_flags = 2;
          pbVar10 = pbVar17;
        }
        param_1->payload = (char *)pbVar10;
        break;
      case cmd_ff:
        pbVar17 = cmd_ff_handle((char *)pbVar17);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_li:
        pbVar17 = cmd_li_handle((char *)pbVar17,0x69);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_tp_test_pattern:
        uVar11 = parse_digits((char *)pbVar17,1);
        if ((uVar11 == 0xffffffff) || (7 < uVar11)) {
          cmd_flags = 2;
          uVar11 = g_test_pattern;
        }
        g_test_pattern = uVar11;
        param_1->payload = pcVar13 + 4;
        break;
      case cmd_tl_test_leds:
        g_led_failures = test_leds();
        break;
      case cmd_ut:
        bVar16 = *pbVar17;
        param_1->payload = pcVar13 + 4;
        g_mode_change_clears = (uint)(bVar16 != 0x4e);
        break;
      case cmd_ud:
        bVar16 = *pbVar17;
        if (bVar16 == 0x2a) {
          g_timeout_command_string._0_1_ = '\0';
          TWI_data.timeout_cmd_str[0] = 0xffffffff;
          g_TWI_dirty_flags = g_TWI_dirty_flags | 0xc;
          pbVar10 = (byte *)(pcVar13 + 4);
        }
        else {
          psVar12 = &TWI_data;
          iVar3 = 0;
          do {
            iVar4 = iVar3;
            pbVar10 = pbVar17;
            if ((bVar16 == 0x5c) && (pbVar17[1] == 0x2a)) {
              pbVar10 = pbVar17 + 1;
            }
            pbVar17 = pbVar10 + 1;
            bVar16 = *pbVar10;
            *(byte *)psVar12->timeout_cmd_str = bVar16;
            *(byte *)((int)&g_timeout_command_string + iVar4) = bVar16;
            *(undefined1 *)((int)psVar12->timeout_cmd_str + 1) = 0;
            *(undefined1 *)((int)&g_timeout_command_string + iVar4 + 1) = 0;
            if (iVar4 + 1 == 0x7d) {
              g_timeout_command_string._0_1_ = '\0';
              cmd_flags = 2;
              goto LAB_2001f338;
            }
            bVar16 = *pbVar17;
            psVar12 = (struct_TWI_data *)((int)&psVar12->field0_0x0 + 1);
            iVar3 = iVar4 + 1;
          } while (bVar16 != 0x2a);
          *(undefined1 *)((int)TWI_data.timeout_cmd_str + iVar4 + 1) = 10;
          *(undefined1 *)((int)&g_timeout_command_string + iVar4 + 1) = 10;
          *(undefined1 *)((int)TWI_data.timeout_cmd_str + iVar4 + 2) = 0x2e;
          *(undefined1 *)((int)&g_timeout_command_string + iVar4 + 2) = 0x2e;
          *(undefined1 *)((int)TWI_data.timeout_cmd_str + iVar4 + 3) = 0;
          *(undefined1 *)((int)&g_timeout_command_string + iVar4 + 3) = 0;
          g_TWI_dirty_flags = g_TWI_dirty_flags | 0xc;
LAB_2001f338:
          pbVar10 = pbVar10 + 2;
        }
        param_1->payload = (char *)pbVar10;
        break;
      case cmd_rd:
        if ((char)g_timeout_command_string == '\0') {
          pcVar6 = strcpy((char *)local_4040,"No Timeout Set  ");
        }
        else {
          pcVar6 = strcpy((char *)local_4040,(char *)&g_timeout_command_string);
        }
        pcVar6[-2] = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_rj:
        pcVar6 = strcpy((char *)local_4040,&DAT_20187314);
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        break;
      case cmd_cc:
        local_4040[0].ptr = (char *)CONCAT31(local_4040[0].ptr._1_3_,*pbVar17);
        if (*pbVar17 == 0x46) {
          local_4040[0].ptr._2_2_ = SUB42(pcVar6,2);
          local_4040[0].ptr._0_2_ = CONCAT11(pcVar13[4],*pbVar17);
          puVar22 = (undefined1 *)((int)&local_4040[0].ptr + 2);
        }
        else {
          puVar22 = (undefined1 *)((int)&local_4040[0].ptr + 1);
        }
        *puVar22 = 0x2d;
        uVar11 = (uint)*pbVar17;
        pcVar6 = pcVar13 + 5;
        if (uVar11 == 0x46) {
          uVar11 = ((byte)pcVar13[4] - 0x30) * 0x100 | 0x46;
        }
        else {
          pcVar6 = pcVar13 + 4;
        }
        pbVar17 = (byte *)(pcVar6 + 1);
        if (*pcVar6 == ':') {
          if (false) {
switchD_2001f450_caseD_42:
            cmd_flags = 2;
            goto LAB_2001f594;
          }
          switch(uVar11 & 0xff) {
          case 0x41:
            uVar11 = 2;
            break;
          default:
            goto switchD_2001f450_caseD_42;
          case 0x43:
            uVar11 = 7;
            break;
          case 0x46:
            uVar11 = (uVar11 >> 8 & 0xff) + 2;
            break;
          case 0x4d:
            uVar11 = 8;
            break;
          case 0x53:
            uVar11 = 1;
          }
          uVar23 = 0;
          for (uVar20 = uVar23; cVar15 = (&DAT_20187314)[uVar20], cVar15 != '\0' && uVar23 != uVar11
              ; uVar20 = uVar20 + 1) {
            if (cVar15 == ':') {
              uVar23 = uVar23 + 1;
            }
          }
          if ((8 < uVar23) || (cVar15 == '\0')) {
            cmd_flags = 2;
            goto LAB_2001f594;
          }
          pbVar10 = &DAT_20187315 + uVar20;
          do {
            uVar23 = uVar20;
            uVar11 = (uint)*pbVar10;
            if (uVar11 == 10) goto LAB_2001f57c;
          } while ((((0x19 < uVar11 - 0x41) && (0x19 < uVar11 - 0x61)) && (9 < uVar11 - 0x30)) &&
                  (pbVar10 = pbVar10 + 1, uVar20 = uVar23 + 1, uVar11 != 0));
          if (*pbVar10 == 10 || *pbVar10 == 0) {
LAB_2001f57c:
            cmd_flags = 2;
            goto LAB_2001f594;
          }
          if (uVar23 == 0xfffffffe) goto LAB_2001f594;
          if (((&DAT_20187315)[uVar23] == 'N') && ((&DAT_20187316)[uVar23] == 'A')) {
            if ((*pbVar17 == 0x4e) && (pcVar6[2] == 'A')) {
              pbVar17 = (byte *)(pcVar6 + 3);
              goto LAB_2001f764;
            }
            cmd_flags = 2;
            goto LAB_2001f750;
          }
          bVar21 = true;
          pbVar10 = &DAT_20187315 + uVar23;
          do {
            uVar11 = (uint)*pbVar17;
            if (uVar11 == 0) {
LAB_2001f624:
              cmd_flags = 2;
              goto LAB_2001f750;
            }
            uVar20 = uVar11 - 0x41;
            bVar25 = 0x18 < uVar20;
            bVar24 = uVar20 == 0x19;
            if (0x19 < uVar20) {
              bVar25 = 8 < uVar11 - 0x30;
              bVar24 = uVar11 - 0x30 == 9;
            }
            if (bVar25 && !bVar24) goto LAB_2001f624;
            pbVar17 = pbVar17 + 1;
            if (*pbVar10 != uVar11) {
              bVar21 = false;
            }
            pbVar10 = pbVar10 + 1;
          } while (pbVar17 != (byte *)(pcVar6 + 9));
          pbVar17 = (byte *)(pcVar6 + 8);
          if (!bVar21) goto LAB_2001f750;
LAB_2001f764:
          pcVar6 = strcpy(puVar22 + 1,"Pass");
        }
        else {
LAB_2001f594:
          cmd_flags = cmd_flags | 2;
LAB_2001f750:
          pcVar6 = strcpy(puVar22 + 1,"Fail");
        }
        *pcVar6 = '\0';
        reply_add_field((char *)local_4040,(int)pcVar6 - (int)local_4040);
        param_1->payload = (char *)pbVar17;
        break;
      case cmd_?F:
        pcVar6 = pcVar13 + 4;
        if (*pbVar17 == 0x2b) {
          g_detailed_diag_info_flag = 1;
        }
        else if (*pbVar17 == 0x2d) {
          g_detailed_diag_info_flag = 0;
        }
        else {
          g_detailed_diag_info_flag = 2;
          pcVar6 = pcVar13 + 3;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_Fx:
        local_3d._5_4_ = 0;
        if (*pbVar17 == 0x50 || *pbVar17 == 0x20) {
          do {
            pbVar17 = pbVar17 + 1;
          } while (*pbVar17 == 0x50 || *pbVar17 == 0x20);
        }
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        if (local_3d._5_4_ == 0xffffffff) {
          reply_code = 0xed;
          cmd_flags = 2;
        }
        else if ((uint)local_3d._5_4_ < 10) {
          g_flash = local_3d._5_4_;
        }
        else {
          reply_code = 0xee;
          cmd_flags = 2;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_Fs:
        local_3d._5_4_ = 0;
        if (*pbVar17 == 0x50 || *pbVar17 == 0x20) {
          do {
            pbVar17 = pbVar17 + 1;
          } while (*pbVar17 == 0x50 || *pbVar17 == 0x20);
        }
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        if (local_3d._5_4_ == 0xffffffff) {
          reply_code = 0xea;
          cmd_flags = 2;
        }
        else if ((uint)local_3d._5_4_ < 0x32) {
          reply_code = 0xeb;
          cmd_flags = 2;
        }
        else if ((uint)local_3d._5_4_ < 0xa1) {
          g_bright_clock_ctrl = division(0x8ca00,g_rows_per_line * local_3d._5_4_);
          ISR_drive_setup();
        }
        else {
          reply_code = 0xec;
          cmd_flags = 2;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_LS_light_sensor:
        local_3d._5_4_ = 0;
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        if (local_3d._5_4_ == 0xffffffff) {
          cmd_flags = 2;
        }
        else if (&DAT_00001388 < (undefined1 *)(local_3d._5_4_ - 1)) {
          cmd_flags = 2;
        }
        else {
          DAT_200238cc = local_3d._5_4_;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_Dc:
        cmd_Dc_handle();
        break;
      case cmd_uu:
        if (*pbVar17 == 0x4e) {
          g_fixed_width_font_flag = 0;
        }
        else if (*pbVar17 == 0x59) {
          g_fixed_width_font_flag = 1;
        }
        else {
          cmd_flags = 2;
        }
        param_1->payload = pcVar13 + 4;
        break;
      case cmd_uo:
        if (DAT_2002394c != 0xffffffff) {
          g_dlmx = DAT_2002394c;
        }
        break;
      case cmd_BE_debug:
        iVar3 = 0;
        pcVar6 = pcVar13 + 4;
        do {
          pcVar13 = pcVar6;
          if ("debug-1"[iVar3] != pcVar13[-1]) {
            cmd_flags = 2;
            goto LAB_2001cbd0;
          }
          if (pcVar13[-1] == '\0') break;
          iVar3 = iVar3 + 1;
          pcVar6 = pcVar13 + 1;
        } while (iVar3 != 7);
        if (*pcVar13 == 'N') {
          g_debug_flag = 0;
        }
        else if (*pcVar13 == 'Y') {
          g_debug_flag = 1;
        }
        else {
          cmd_flags = 2;
        }
        pcVar13 = pcVar13 + 1;
LAB_2001cbd0:
        param_1->payload = pcVar13;
        break;
      case cmd_DR:
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        if (local_3d._5_4_ == 0xffffffff) {
          cmd_flags = 2;
        }
        else {
          g_ISR_timer1_gate = local_3d._5_4_;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_DD:
        pcVar6 = (char *)cmd_DD_handle((uint)(byte)param_1->port,(int)pbVar17);
        param_1->payload = pcVar6;
        break;
      case cmd_qe_twi_dump:
        pcVar6 = atoi((char *)pbVar17,&local_2c);
        param_1->payload = pcVar6 + 1;
        pcVar6 = atoi(pcVar6 + 1,&local_28);
        param_1->payload = pcVar6;
        cmd_qe_i2c_mem_dump((uint)(byte)param_1->port,local_2c,local_28);
        break;
      case cmd_ur:
        bVar16 = *pbVar17;
        param_1->payload = pcVar13 + 4;
        DAT_20174730 = (uint)(bVar16 == 0x4e);
        break;
      case cmd_ux:
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        if ((int)local_3d._5_4_ < 0) {
          cmd_flags = 2;
        }
        else {
          if ((uint)local_3d._5_4_ < DAT_20023950) {
            local_3d._5_4_ = DAT_20023950;
          }
          if (100 < (uint)local_3d._5_4_) {
            local_3d._5_4_ = 100;
          }
          g_max_brightness = local_3d._5_4_;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_uw:
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        if ((int)local_3d._5_4_ < 0) {
          cmd_flags = 2;
        }
        else {
          if (100 < (uint)local_3d._5_4_) {
            local_3d._5_4_ = 100;
          }
          DAT_20023950 = local_3d._5_4_;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_uy:
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        if ((int)local_3d._5_4_ < 0) {
          cmd_flags = 2;
        }
        else {
          if (DAT_20023954 < (uint)local_3d._5_4_) {
            local_3d._5_4_ = DAT_20023954;
          }
          g_min_brightness = local_3d._5_4_;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_ui:
        pcVar6 = atoi((char *)pbVar17,(uint *)(local_3d + 5));
        if ((int)local_3d._5_4_ < 0) {
          cmd_flags = 2;
        }
        else {
          if (100 < (uint)local_3d._5_4_) {
            local_3d._5_4_ = 100;
          }
          DAT_20023954 = local_3d._5_4_;
        }
        param_1->payload = pcVar6;
        break;
      case cmd_NB:
        bVar21 = *pbVar17 == 0x59 || *pbVar17 == 0x79;
        if (bVar21) {
          g_master_mode = 0;
        }
        g_next_bus_ddx = (uint)bVar21;
        param_1->payload = pcVar13 + 4;
        break;
      case cmd_?N:
        local_4040[0].ptr = (char *)0x666f424e;
        local_4040[0].count = CONCAT22(local_4040[0].count._2_2_,0x66);
        psVar9 = (struct_cmd_buf *)local_3d;
        memcpy(psVar9,"NBon",5);
        if (g_next_bus_ddx == 1) {
          iVar3 = 4;
        }
        else {
          psVar9 = local_4040;
          iVar3 = 5;
        }
        reply_add_field((char *)psVar9,iVar3);
      }
    }
    local_4048 = param_1->payload + ((int)local_4048 - (int)pcVar18);
    bVar21 = true;
  } while( true );
}

