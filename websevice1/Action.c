Action()
{
	int i=0;

//调用获取城市接口 返回城市列表
	web_service_call( "StepName=getDomesticCity_101",
		"SOAPMethod=DomesticAirline|DomesticAirlineSoap|getDomesticCity",
		"ResponseParam=response",
		"Service=DomesticAirline",
		"ExpectedResponse=SoapResult",
		"Snapshot=t1478401290.inf",
		BEGIN_ARGUMENTS,
		END_ARGUMENTS,
		BEGIN_RESULT,
		END_RESULT,
		LAST);

/* 第一种用法
	//将返回值（城市名）的第50个值，存成一个ParamValue_Abbreviation变量的值
	lr_xml_get_values("XML={response}",
	                  "FastQuery=/Envelope/Body/getDomesticCityResponse/getDomesticCityResult/diffgram/Airline1/Address[50]/Abbreviation",
	                  "ValueParam=ParamValue_Abbreviation",
	                  LAST);*/
              
//将返回值（城市名）的第50个值，存成一个ParamValue_Abbreviation变量的值，ParamValue_Abbreviation有多个值，是一个数组
	i=lr_xml_get_values("XML={response}",
	                  "Query=/Envelope/Body/getDomesticCityResponse/getDomesticCityResult/diffgram/Airline1/Address[*]/Abbreviation",
	                  "ValueParam=ParamValue_Abbreviation",
	                  "SelectAll=yes",
	                  LAST);



	lr_save_int(i, "ParamValue_Abbreviation_count");
//根据lr_paramarr_random的语法设置ParamValue_Abbreviation_count的值 (注意这里的count的c是小写的)

//lr_output_message(lr_paramarr_random("ParamValue_Abbreviation")); //打印随机取数组中的那个下标值

	lr_save_string( lr_paramarr_random("ParamValue_Abbreviation"),
		"lastCity" );
//将随机取的目的地存成lastcity变量的值


//再调用航班请求函数，将从上海出发到变量到{ParamValue_Abbreviation}值的目的地
	web_service_call( "StepName=getDomesticAirlinesTime_102",
		"SOAPMethod=DomesticAirline|DomesticAirlineSoap|getDomesticAirlinesTime",
		"ResponseParam=response",
		"Service=DomesticAirline",
		"ExpectedResponse=SoapResult",
		"Snapshot=t1478402071.inf",
		BEGIN_ARGUMENTS,
		"startCity=SHA",
		"lastCity=ZHA",
		"theDate={NewParam}",
		"userID=",
		END_ARGUMENTS,
		BEGIN_RESULT,
		END_RESULT,
		LAST);



	//获得航空公司名
	lr_xml_get_values("XML={response}",
	                  "FastQuery=/Envelope/Body/getDomesticAirlinesTimeResponse/getDomesticAirlinesTimeResult/diffgram/Airlines/AirlinesTime/Company",
	                  "ValueParam=ParamValue_Company",
	                  LAST);

	//取出航空公司名的方法
	lr_output_message(lr_eval_string("{ParamValue_Company}"));

	//增加断言
	if (strcmp(lr_eval_string("{ParamValue_Company}"),"东方航空")==0)
		lr_output_message("PASS");
	else
		lr_output_message("Fail");

}
