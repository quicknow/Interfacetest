Action()
{
	int i=0;

//���û�ȡ���нӿ� ���س����б�
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

/* ��һ���÷�
	//������ֵ�����������ĵ�50��ֵ�����һ��ParamValue_Abbreviation������ֵ
	lr_xml_get_values("XML={response}",
	                  "FastQuery=/Envelope/Body/getDomesticCityResponse/getDomesticCityResult/diffgram/Airline1/Address[50]/Abbreviation",
	                  "ValueParam=ParamValue_Abbreviation",
	                  LAST);*/
              
//������ֵ�����������ĵ�50��ֵ�����һ��ParamValue_Abbreviation������ֵ��ParamValue_Abbreviation�ж��ֵ����һ������
	i=lr_xml_get_values("XML={response}",
	                  "Query=/Envelope/Body/getDomesticCityResponse/getDomesticCityResult/diffgram/Airline1/Address[*]/Abbreviation",
	                  "ValueParam=ParamValue_Abbreviation",
	                  "SelectAll=yes",
	                  LAST);



	lr_save_int(i, "ParamValue_Abbreviation_count");
//����lr_paramarr_random���﷨����ParamValue_Abbreviation_count��ֵ (ע�������count��c��Сд��)

//lr_output_message(lr_paramarr_random("ParamValue_Abbreviation")); //��ӡ���ȡ�����е��Ǹ��±�ֵ

	lr_save_string( lr_paramarr_random("ParamValue_Abbreviation"),
		"lastCity" );
//�����ȡ��Ŀ�ĵش��lastcity������ֵ


//�ٵ��ú����������������Ϻ�������������{ParamValue_Abbreviation}ֵ��Ŀ�ĵ�
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



	//��ú��չ�˾��
	lr_xml_get_values("XML={response}",
	                  "FastQuery=/Envelope/Body/getDomesticAirlinesTimeResponse/getDomesticAirlinesTimeResult/diffgram/Airlines/AirlinesTime/Company",
	                  "ValueParam=ParamValue_Company",
	                  LAST);

	//ȡ�����չ�˾���ķ���
	lr_output_message(lr_eval_string("{ParamValue_Company}"));

	//���Ӷ���
	if (strcmp(lr_eval_string("{ParamValue_Company}"),"��������")==0)
		lr_output_message("PASS");
	else
		lr_output_message("Fail");

}
