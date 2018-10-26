drop table agent_zhxx;

drop table agent_shsxfqjfl;

drop table agent_shys;

drop table agent_shsxfqjfy;

--==============================================================
-- TABLE: "AGENT_ZHXX"
--==============================================================
CREATE 
    TABLE AGENT_ZHXX 
	    ( 
		         ZHHH VARCHAR(32) NOT NULL, 
				         ZHMC VARCHAR(36), 
						         SXFSRZH VARCHAR(32), 
								         SXFDFZH VARCHAR(32), 
										         LXRXM VARCHAR(20), 
												         LXRSJH VARCHAR(11), 
														         SHZT VARCHAR(1), 
																         BLRQ VARCHAR(8), 
																		         WHSJ VARCHAR(8), 
																				         BYZD1 VARCHAR(1), 
																						         BYZD2 VARCHAR(6), 
																								         BYZD3 VARCHAR(10), 
																										         BYZD4 VARCHAR(20), 
																												         BYZD5 VARCHAR(50), 
																														         BYZD6 VARCHAR(200), 
																																         CONSTRAINT P_K_AGENT_ZHXX_1 PRIMARY KEY (ZHHH) 
																																		     ); 
		comment on table AGENT_ZHXX is
		'支行信息表'; 
		comment on column AGENT_ZHXX.ZHHH is
		'支行行号'; 
		comment on column AGENT_ZHXX.ZHMC is
		'支行名称'; 
		comment on column AGENT_ZHXX.SXFSRZH is
		'手续费收入账号'; 
		comment on column AGENT_ZHXX.SXFDFZH is
		'手续费垫付账号'; 
		comment on column AGENT_ZHXX.LXRXM is
		'联系人姓名'; 
		comment on column AGENT_ZHXX.LXRSJH is
		'联系人手机号'; 
		comment on column AGENT_ZHXX.SHZT is
		'审核状态'; 
		comment on column AGENT_ZHXX.BLRQ is
		'办理日期'; 
		comment on column AGENT_ZHXX.WHSJ is
		'维护时间'; 
		comment on column AGENT_ZHXX.BYZD1 is
		'备用字段1'; 
		comment on column AGENT_ZHXX.BYZD2 is
		'备用字段2'; 
		comment on column AGENT_ZHXX.BYZD3 is
		'备用字段3'; 
		comment on column AGENT_ZHXX.BYZD4 is
		'备用字段4'; 
		comment on column AGENT_ZHXX.BYZD5 is
		'备用字段5'; 
		comment on column AGENT_ZHXX.BYZD6 is
		'备用字段6';


		--==============================================================
		-- TABLE: "AGENT_SHSXFQJFL"
		--==============================================================
		CREATE TABLE AGENT_SHSXFQJFL 
		    ( 
			         ZXJE VARCHAR(16), 
					         ZDJE VARCHAR(16), 
							         FL VARCHAR(6), 
									         BYZD1 VARCHAR(1), 
											         BYZD2 VARCHAR(6), 
													         BYZD3 VARCHAR(10), 
															         BYZD4 VARCHAR(20), 
																	         BYZD5 VARCHAR(50), 
																			         QJLX VARCHAR(1) 
																					     )
			    ; 
				comment on table AGENT_SHSXFQJFL is
				'商户手续费区间费率表'; 
				comment on column AGENT_SHSXFQJFL.ZXJE is
				'最小金额'; 
				comment on column AGENT_SHSXFQJFL.ZDJE is
				'最大金额'; 
				comment on column AGENT_SHSXFQJFL.FL is
				'费率'; 
				comment on column AGENT_SHSXFQJFL.BYZD1 is
				'备用字段1'; 
				comment on column AGENT_SHSXFQJFL.BYZD2 is
				'备用字段2'; 
				comment on column AGENT_SHSXFQJFL.BYZD3 is
				'备用字段3'; 
				comment on column AGENT_SHSXFQJFL.BYZD4 is
				'备用字段4'; 
				comment on column AGENT_SHSXFQJFL.BYZD5 is
				'备用字段5';
				comment on column AGENT_SHSXFQJFL.QJLX is
				'区间类型';


				--==============================================================
				-- TABLE: "AGENT_SHYS"
				--==============================================================
				CREATE 
				    TABLE AGENT_SHYS 
					    ( 
						         DJFSHH VARCHAR(32) NOT NULL, 
								         DJFSHMC VARCHAR(32), 
										         XLSHH VARCHAR(32), 
												         SXFZFF VARCHAR(1), 
														         SXFFLGZ VARCHAR(8), 
																         SFFL VARCHAR(8), 
																		         SFFY VARCHAR(8), 
																				         SSZH VARCHAR(32), 
																						         SHZT VARCHAR(1), 
																								         ZFFS VARCHAR(1) NOT NULL, 
																										         BYZD1 VARCHAR(1), 
																												         BYZD2 VARCHAR(6), 
																														         BYZD3 VARCHAR(10), 
																																         BYZD4 VARCHAR(20), 
																																		         BYZD5 VARCHAR(50), 
																																				         BYZD6 VARCHAR(200), 
																																						         CONSTRAINT P_K_AGENT_SHYS_1 PRIMARY KEY (DJFSHH, ZFFS) 
																																								     )
						    ; 
							comment on table AGENT_SHYS is
							'商户映射表'; 
							comment on column AGENT_SHYS.DJFSHH is
							'D缴费商户号'; 
							comment on column AGENT_SHYS.DJFSHMC is
							'D缴费商户名称'; 
							comment on column AGENT_SHYS.XLSHH is
							'讯联商户号'; 
							comment on column AGENT_SHYS.SXFZFF is
							'手续费支付方'; 
							comment on column AGENT_SHYS.SXFFLGZ is
							'手续费费率规则'; 
							comment on column AGENT_SHYS.SFFL is
							'收费费率'; 
							comment on column AGENT_SHYS.SFFY is
							'收费费用'; 
							comment on column AGENT_SHYS.SSZH is
							'所属支行'; 
							comment on column AGENT_SHYS.SHZT is
							'审核状态'; 
							comment on column AGENT_SHYS.ZFFS is
							'支付方式'; 
							comment on column AGENT_SHYS.BYZD1 is
							'备用字段1'; 
							comment on column AGENT_SHYS.BYZD2 is
							'备用字段2'; 
							comment on column AGENT_SHYS.BYZD3 is
							'备用字段3'; 
							comment on column AGENT_SHYS.BYZD4 is
							'备用字段4'; 
							comment on column AGENT_SHYS.BYZD5 is
							'备用字段5'; 
							comment on column AGENT_SHYS.BYZD6 is
							'备用字段6';


							--==============================================================
							-- TABLE: "AGENT_SHSXFQJFY"
							--==============================================================
							CREATE TABLE AGENT_SHSXFQJFY 
							    ( 
								         ZXJE VARCHAR(16), 
										         ZDJE VARCHAR(16), 
												         FY VARCHAR(6), 
														         BYZD1 VARCHAR(1), 
																         BYZD2 VARCHAR(6), 
																		         BYZD3 VARCHAR(10), 
																				         BYZD4 VARCHAR(20), 
																						         BYZD5 VARCHAR(50), 
																								         QJLX VARCHAR(1) 
																										     )
								    ; 
									comment on table AGENT_SHSXFQJFY is
									'商户手续费区间费用表'; 
									comment on column AGENT_SHSXFQJFY.ZXJE is
									'最小金额'; 
									comment on column AGENT_SHSXFQJFY.ZDJE is
									'最大金额'; 
									comment on column AGENT_SHSXFQJFY.FY is
									'费用'; 
									comment on column AGENT_SHSXFQJFY.BYZD1 is
									'备用字段1'; 
									comment on column AGENT_SHSXFQJFY.BYZD2 is
									'备用字段2'; 
									comment on column AGENT_SHSXFQJFY.BYZD3 is
									'备用字段3'; 
									comment on column AGENT_SHSXFQJFY.BYZD4 is
									'备用字段4'; 
									comment on column AGENT_SHSXFQJFY.BYZD5 is
									'备用字段5';
									comment on column AGENT_SHSXFQJFL.QJLX is
									'区间类型';
