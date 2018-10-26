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
		'֧����Ϣ��'; 
		comment on column AGENT_ZHXX.ZHHH is
		'֧���к�'; 
		comment on column AGENT_ZHXX.ZHMC is
		'֧������'; 
		comment on column AGENT_ZHXX.SXFSRZH is
		'�����������˺�'; 
		comment on column AGENT_ZHXX.SXFDFZH is
		'�����ѵ渶�˺�'; 
		comment on column AGENT_ZHXX.LXRXM is
		'��ϵ������'; 
		comment on column AGENT_ZHXX.LXRSJH is
		'��ϵ���ֻ���'; 
		comment on column AGENT_ZHXX.SHZT is
		'���״̬'; 
		comment on column AGENT_ZHXX.BLRQ is
		'��������'; 
		comment on column AGENT_ZHXX.WHSJ is
		'ά��ʱ��'; 
		comment on column AGENT_ZHXX.BYZD1 is
		'�����ֶ�1'; 
		comment on column AGENT_ZHXX.BYZD2 is
		'�����ֶ�2'; 
		comment on column AGENT_ZHXX.BYZD3 is
		'�����ֶ�3'; 
		comment on column AGENT_ZHXX.BYZD4 is
		'�����ֶ�4'; 
		comment on column AGENT_ZHXX.BYZD5 is
		'�����ֶ�5'; 
		comment on column AGENT_ZHXX.BYZD6 is
		'�����ֶ�6';


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
				'�̻�������������ʱ�'; 
				comment on column AGENT_SHSXFQJFL.ZXJE is
				'��С���'; 
				comment on column AGENT_SHSXFQJFL.ZDJE is
				'�����'; 
				comment on column AGENT_SHSXFQJFL.FL is
				'����'; 
				comment on column AGENT_SHSXFQJFL.BYZD1 is
				'�����ֶ�1'; 
				comment on column AGENT_SHSXFQJFL.BYZD2 is
				'�����ֶ�2'; 
				comment on column AGENT_SHSXFQJFL.BYZD3 is
				'�����ֶ�3'; 
				comment on column AGENT_SHSXFQJFL.BYZD4 is
				'�����ֶ�4'; 
				comment on column AGENT_SHSXFQJFL.BYZD5 is
				'�����ֶ�5';
				comment on column AGENT_SHSXFQJFL.QJLX is
				'��������';


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
							'�̻�ӳ���'; 
							comment on column AGENT_SHYS.DJFSHH is
							'D�ɷ��̻���'; 
							comment on column AGENT_SHYS.DJFSHMC is
							'D�ɷ��̻�����'; 
							comment on column AGENT_SHYS.XLSHH is
							'Ѷ���̻���'; 
							comment on column AGENT_SHYS.SXFZFF is
							'������֧����'; 
							comment on column AGENT_SHYS.SXFFLGZ is
							'�����ѷ��ʹ���'; 
							comment on column AGENT_SHYS.SFFL is
							'�շѷ���'; 
							comment on column AGENT_SHYS.SFFY is
							'�շѷ���'; 
							comment on column AGENT_SHYS.SSZH is
							'����֧��'; 
							comment on column AGENT_SHYS.SHZT is
							'���״̬'; 
							comment on column AGENT_SHYS.ZFFS is
							'֧����ʽ'; 
							comment on column AGENT_SHYS.BYZD1 is
							'�����ֶ�1'; 
							comment on column AGENT_SHYS.BYZD2 is
							'�����ֶ�2'; 
							comment on column AGENT_SHYS.BYZD3 is
							'�����ֶ�3'; 
							comment on column AGENT_SHYS.BYZD4 is
							'�����ֶ�4'; 
							comment on column AGENT_SHYS.BYZD5 is
							'�����ֶ�5'; 
							comment on column AGENT_SHYS.BYZD6 is
							'�����ֶ�6';


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
									'�̻�������������ñ�'; 
									comment on column AGENT_SHSXFQJFY.ZXJE is
									'��С���'; 
									comment on column AGENT_SHSXFQJFY.ZDJE is
									'�����'; 
									comment on column AGENT_SHSXFQJFY.FY is
									'����'; 
									comment on column AGENT_SHSXFQJFY.BYZD1 is
									'�����ֶ�1'; 
									comment on column AGENT_SHSXFQJFY.BYZD2 is
									'�����ֶ�2'; 
									comment on column AGENT_SHSXFQJFY.BYZD3 is
									'�����ֶ�3'; 
									comment on column AGENT_SHSXFQJFY.BYZD4 is
									'�����ֶ�4'; 
									comment on column AGENT_SHSXFQJFY.BYZD5 is
									'�����ֶ�5';
									comment on column AGENT_SHSXFQJFL.QJLX is
									'��������';
