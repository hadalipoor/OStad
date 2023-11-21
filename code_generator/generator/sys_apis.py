system_apis = """
{
	"info": {
		"_postman_id": "2a331397-a133-4d9c-9937-a09a939a7511",
		"name": "ESP",
		"schema": "https://schema.getpostman.com/json/collection/v2.1.0/collection.json",
		"_exporter_id": "935248"
	},
	"item": [
		{
			"name": "Ostad",
			"item": [
				{
					"name": "Clock",
					"item": [
						{
							"name": "now",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "http://192.168.1.103/clock/now",
									"protocol": "http",
									"host": [
										"192",
										"168",
										"1",
										"103"
									],
									"path": [
										"clock",
										"now"
									]
								}
							},
							"response": []
						},
						{
							"name": "now Jalali",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "http://192.168.1.103/clock/nowJalali",
									"protocol": "http",
									"host": [
										"192",
										"168",
										"1",
										"103"
									],
									"path": [
										"clock",
										"nowJalali"
									]
								}
							},
							"response": []
						},
						{
							"name": "syncTime",
							"request": {
								"method": "POST",
								"header": [],
								"url": {
									"raw": "http://192.168.1.103/clock/syncTime",
									"protocol": "http",
									"host": [
										"192",
										"168",
										"1",
										"103"
									],
									"path": [
										"clock",
										"syncTime"
									]
								}
							},
							"response": []
						},
						{
							"name": "adjustTime",
							"request": {
								"method": "POST",
								"header": [],
								"url": {
									"raw": "http://192.168.1.103/clock/adjustTime?date=11/19/2023 07:33:00",
									"protocol": "http",
									"host": [
										"192",
										"168",
										"1",
										"103"
									],
									"path": [
										"clock",
										"adjustTime"
									],
									"query": [
										{
											"key": "date",
											"value": "11/19/2023 07:33:00"
										}
									]
								}
							},
							"response": []
						}
					]
				},
				{
					"name": "WiFi",
					"item": [
						{
							"name": "Broadcast",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "10.21.249.1/wifi/broadcast?broadcast=SampleMessage",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"wifi",
										"broadcast"
									],
									"query": [
										{
											"key": "broadcast",
											"value": "SampleMessage"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Restart",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "10.21.249.1/wifi/restart",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"wifi",
										"restart"
									]
								}
							},
							"response": []
						},
						{
							"name": "Disconnect WiFi",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "10.21.249.1/wifi/disconnect_wifi",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"wifi",
										"disconnect_wifi"
									]
								}
							},
							"response": []
						},
						{
							"name": "Forget WiFi",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "10.21.249.1/wifi/forget_wifi?ssid=SAMPLE",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"wifi",
										"forget_wifi"
									],
									"query": [
										{
											"key": "ssid",
											"value": "SAMPLE"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Connect WiFi",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "10.21.249.1/wifi/connect_wifi?ssid=Molkat",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"wifi",
										"connect_wifi"
									],
									"query": [
										{
											"key": "ssid",
											"value": "Molkat"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Add SSID",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "10.21.249.1/wifi/add_ssid?ssid=SAMPLE&password=PASSWORD",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"wifi",
										"add_ssid"
									],
									"query": [
										{
											"key": "ssid",
											"value": "SAMPLE"
										},
										{
											"key": "password",
											"value": "PASSWORD"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Get All SSIDs",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "10.21.249.1/wifi/get_all_ssids",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"wifi",
										"get_all_ssids"
									]
								}
							},
							"response": []
						}
					]
				},
				{
					"name": "File",
					"item": [
						{
							"name": "Browse Folder",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "192.168.1.103/fileApi/browse_folder?path=/",
									"host": [
										"192",
										"168",
										"1",
										"103"
									],
									"path": [
										"fileApi",
										"browse_folder"
									],
									"query": [
										{
											"key": "path",
											"value": "/"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Open File",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "192.168.1.103/fileApi/open?path=/system_config.db",
									"host": [
										"192",
										"168",
										"1",
										"103"
									],
									"path": [
										"fileApi",
										"open"
									],
									"query": [
										{
											"key": "path",
											"value": "/system_config.db"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Delete File",
							"request": {
								"method": "DELETE",
								"header": [],
								"url": {
									"raw": "10.21.249.1/fileApi/delete?path=SamplePath",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"fileApi",
										"delete"
									],
									"query": [
										{
											"key": "path",
											"value": "SamplePath"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Write File",
							"request": {
								"method": "PUT",
								"header": [],
								"url": {
									"raw": "http://10.168.221.1/fileApi/write?path=/db/student/db&content=1,key=db_change_info_save,value=true, 3,key=mesh_root,value=false, 4,key=ap_ssid,value=ESP2, 5,key=wifi_mode_mesh,value=false, 6,key=wifi_mode_wifi,value=true, 7,key=wifi_mode_ap,value=false,",
									"protocol": "http",
									"host": [
										"10",
										"168",
										"221",
										"1"
									],
									"path": [
										"fileApi",
										"write"
									],
									"query": [
										{
											"key": "path",
											"value": "/db/student/db"
										},
										{
											"key": "content",
											"value": "1,key=db_change_info_save,value=true, 3,key=mesh_root,value=false, 4,key=ap_ssid,value=ESP2, 5,key=wifi_mode_mesh,value=false, 6,key=wifi_mode_wifi,value=true, 7,key=wifi_mode_ap,value=false,"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Format File System",
							"request": {
								"method": "PUT",
								"header": [],
								"url": {
									"raw": "10.21.249.1/fileApi/format",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"fileApi",
										"format"
									]
								}
							},
							"response": []
						},
						{
							"name": "Rename File",
							"request": {
								"method": "PUT",
								"header": [],
								"url": {
									"raw": "10.21.249.1/fileApi/rename?path=SamplePath&new_name=NewName",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"fileApi",
										"rename"
									],
									"query": [
										{
											"key": "path",
											"value": "SamplePath"
										},
										{
											"key": "new_name",
											"value": "NewName"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Move File",
							"request": {
								"method": "PUT",
								"header": [],
								"url": {
									"raw": "10.21.249.1/fileApi/move?source_path=SampleSourcePath&destination_path=SampleDestinationPath",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"fileApi",
										"move"
									],
									"query": [
										{
											"key": "source_path",
											"value": "SampleSourcePath"
										},
										{
											"key": "destination_path",
											"value": "SampleDestinationPath"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Copy File",
							"request": {
								"method": "PUT",
								"header": [],
								"url": {
									"raw": "10.21.249.1/fileApi/copy?source_path=SampleSourcePath&destination_path=SampleDestinationPath",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"fileApi",
										"copy"
									],
									"query": [
										{
											"key": "source_path",
											"value": "SampleSourcePath"
										},
										{
											"key": "destination_path",
											"value": "SampleDestinationPath"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Duplicate File",
							"request": {
								"method": "PUT",
								"header": [],
								"url": {
									"raw": "192.168.1.109/fileApi/duplicate?path=SamplePath",
									"host": [
										"192",
										"168",
										"1",
										"109"
									],
									"path": [
										"fileApi",
										"duplicate"
									],
									"query": [
										{
											"key": "path",
											"value": "SamplePath"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Make Folder",
							"request": {
								"method": "PUT",
								"header": [],
								"url": {
									"raw": "192.168.1.109/fileApi/mkdir?path=/Test",
									"host": [
										"192",
										"168",
										"1",
										"109"
									],
									"path": [
										"fileApi",
										"mkdir"
									],
									"query": [
										{
											"key": "path",
											"value": "/Test"
										}
									]
								}
							},
							"response": []
						}
					]
				},
				{
					"name": "SSID",
					"item": [
						{
							"name": "Create SSID",
							"request": {
								"method": "POST",
								"header": [],
								"url": {
									"raw": "192.168.4.1/ssid/create?SSID=Molkat&Password=Bo!2bjaq",
									"host": [
										"192",
										"168",
										"4",
										"1"
									],
									"path": [
										"ssid",
										"create"
									],
									"query": [
										{
											"key": "SSID",
											"value": "Molkat"
										},
										{
											"key": "Password",
											"value": "Bo!2bjaq"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Update SSID",
							"request": {
								"method": "PUT",
								"header": [],
								"url": {
									"raw": "10.21.249.1/ssid/update?id=1&SSID=SampleSSID&Password=SamplePassword",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"ssid",
										"update"
									],
									"query": [
										{
											"key": "id",
											"value": "1"
										},
										{
											"key": "SSID",
											"value": "SampleSSID"
										},
										{
											"key": "Password",
											"value": "SamplePassword"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Delete SSID",
							"request": {
								"method": "DELETE",
								"header": [],
								"url": {
									"raw": "10.21.249.1/ssid/delete?id=1",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"ssid",
										"delete"
									],
									"query": [
										{
											"key": "id",
											"value": "1"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Get SSID",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "10.21.249.1/ssid/get?query=SampleQuery",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"ssid",
										"get"
									],
									"query": [
										{
											"key": "query",
											"value": "SampleQuery"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Get SSID By ID",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "10.21.249.1/ssid/getById?id=1",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"ssid",
										"getById"
									],
									"query": [
										{
											"key": "id",
											"value": "1"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "Get All SSIDs",
							"request": {
								"method": "GET",
								"header": [],
								"url": {
									"raw": "10.21.249.1/ssid/getAll",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"ssid",
										"getAll"
									]
								}
							},
							"response": []
						}
					]
				},
				{
					"name": "AutenticationConfig",
					"item": [
						{
							"name": "delete",
							"request": {
								"method": "DELETE",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "192.168.1.102/authenticationConfig/delete?id=5",
									"host": [
										"192",
										"168",
										"1",
										"102"
									],
									"path": [
										"authenticationConfig",
										"delete"
									],
									"query": [
										{
											"key": "id",
											"value": "5"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "create",
							"request": {
								"method": "POST",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "http://192.168.4.1/authenticationConfig/create?key=db_change_info_save&value=false",
									"protocol": "http",
									"host": [
										"192",
										"168",
										"4",
										"1"
									],
									"path": [
										"authenticationConfig",
										"create"
									],
									"query": [
										{
											"key": "key",
											"value": "db_change_info_save"
										},
										{
											"key": "value",
											"value": "false"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "update",
							"request": {
								"method": "PUT",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "192.168.1.109/authenticationConfig/update?id=4&key=wifi_mode_mesh&value=true",
									"host": [
										"192",
										"168",
										"1",
										"109"
									],
									"path": [
										"authenticationConfig",
										"update"
									],
									"query": [
										{
											"key": "id",
											"value": "4"
										},
										{
											"key": "key",
											"value": "wifi_mode_mesh"
										},
										{
											"key": "value",
											"value": "true"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "submit",
							"request": {
								"method": "PUT",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "192.168.1.101/authenticationConfig/submit?key=mesh_root&value=false",
									"host": [
										"192",
										"168",
										"1",
										"101"
									],
									"path": [
										"authenticationConfig",
										"submit"
									],
									"query": [
										{
											"key": "key",
											"value": "mesh_root"
										},
										{
											"key": "value",
											"value": "false"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "getAll",
							"protocolProfileBehavior": {
								"disableBodyPruning": true
							},
							"request": {
								"method": "GET",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "http://192.168.1.101/authenticationConfig/getAll",
									"protocol": "http",
									"host": [
										"192",
										"168",
										"1",
										"101"
									],
									"path": [
										"authenticationConfig",
										"getAll"
									]
								}
							},
							"response": []
						},
						{
							"name": "getById",
							"protocolProfileBehavior": {
								"disableBodyPruning": true
							},
							"request": {
								"method": "GET",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "192.168.1.101/authenticationConfig/getById?id=1",
									"host": [
										"192",
										"168",
										"1",
										"101"
									],
									"path": [
										"authenticationConfig",
										"getById"
									],
									"query": [
										{
											"key": "id",
											"value": "1"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "get",
							"protocolProfileBehavior": {
								"disableBodyPruning": true
							},
							"request": {
								"method": "GET",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "192.168.1.101/authenticationConfig/getById?id=1",
									"host": [
										"192",
										"168",
										"1",
										"101"
									],
									"path": [
										"authenticationConfig",
										"getById"
									],
									"query": [
										{
											"key": "id",
											"value": "1"
										}
									]
								}
							},
							"response": []
						}
					]
				},
				{
					"name": "SystemConfig",
					"item": [
						{
							"name": "delete",
							"request": {
								"method": "DELETE",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "192.168.1.103/systemConfig/delete?id=5",
									"host": [
										"192",
										"168",
										"1",
										"103"
									],
									"path": [
										"systemConfig",
										"delete"
									],
									"query": [
										{
											"key": "id",
											"value": "5"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "create",
							"request": {
								"method": "POST",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "http://192.168.4.1/systemConfig/create?key=db_change_info_save&value=false",
									"protocol": "http",
									"host": [
										"192",
										"168",
										"4",
										"1"
									],
									"path": [
										"systemConfig",
										"create"
									],
									"query": [
										{
											"key": "key",
											"value": "db_change_info_save"
										},
										{
											"key": "value",
											"value": "false"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "update",
							"request": {
								"method": "PUT",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "192.168.1.109/systemConfig/update?id=4&key=wifi_mode_mesh&value=true",
									"host": [
										"192",
										"168",
										"1",
										"109"
									],
									"path": [
										"systemConfig",
										"update"
									],
									"query": [
										{
											"key": "id",
											"value": "4"
										},
										{
											"key": "key",
											"value": "wifi_mode_mesh"
										},
										{
											"key": "value",
											"value": "true"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "submit",
							"request": {
								"method": "PUT",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "10.21.249.1/systemConfig/submit?key=mesh_root&value=false",
									"host": [
										"10",
										"21",
										"249",
										"1"
									],
									"path": [
										"systemConfig",
										"submit"
									],
									"query": [
										{
											"key": "key",
											"value": "mesh_root"
										},
										{
											"key": "value",
											"value": "false"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "getAll",
							"protocolProfileBehavior": {
								"disableBodyPruning": true
							},
							"request": {
								"auth": {
									"type": "bearer",
									"bearer": [
										{
											"key": "token",
											"value": "qdv66/UtLWjJCeWXodHijy9l4vfnrE6l/e8U6Fx/aAM=",
											"type": "string"
										}
									]
								},
								"method": "GET",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "http://192.168.1.101/systemConfig/getAll",
									"protocol": "http",
									"host": [
										"192",
										"168",
										"1",
										"101"
									],
									"path": [
										"systemConfig",
										"getAll"
									]
								}
							},
							"response": []
						},
						{
							"name": "getById",
							"protocolProfileBehavior": {
								"disableBodyPruning": true
							},
							"request": {
								"method": "GET",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "192.168.1.101/systemConfig/getById?id=1",
									"host": [
										"192",
										"168",
										"1",
										"101"
									],
									"path": [
										"systemConfig",
										"getById"
									],
									"query": [
										{
											"key": "id",
											"value": "1"
										}
									]
								}
							},
							"response": []
						},
						{
							"name": "get",
							"protocolProfileBehavior": {
								"disableBodyPruning": true
							},
							"request": {
								"method": "GET",
								"header": [],
								"body": {
									"mode": "raw",
									"raw": "",
									"options": {
										"raw": {
											"language": "javascript"
										}
									}
								},
								"url": {
									"raw": "192.168.1.101/systemConfig/getById?id=1",
									"host": [
										"192",
										"168",
										"1",
										"101"
									],
									"path": [
										"systemConfig",
										"getById"
									],
									"query": [
										{
											"key": "id",
											"value": "1"
										}
									]
								}
							},
							"response": []
						}
					]
				}
			]
		}
	]
}"""
