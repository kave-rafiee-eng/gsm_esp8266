

void read_json_advance(){

  char temp_connection_test[50];
  char temp_serial[50];
  char temp_url[50];  

  String connection_test = doc["connection_test"];
  String serial = doc["serial"];
  String url = doc["url"];

  Serial.print("connection_test = ");
  Serial.println( connection_test);
  Serial.println( "  ------   " );
  Serial.print("serial = ");
  Serial.println( serial);
  Serial.println( "  ------   " );
  Serial.print("url = ");
  Serial.println( url);
  Serial.println( "  ------   " );

  Serial.println(" ");

  Serial.println("-- JSON EXTEND ---");
  

  if( serial == "null"){}
  else { 
    serial.toCharArray(temp_serial, serial.length()+1);
    strncpy(advance_json_serial, temp_serial, sizeof advance_json_serial);   
    advance_serial_F=1;
    send_to_server_F=1;
    //Serial.print("seial = ");
    //Serial.println( temp_serial);
  }

  if( url == "null"){}
  else { 
    advance_url_F=1;
    url.toCharArray(temp_url, url.length()+1);
    strncpy(advance_json_url, temp_url, sizeof advance_json_url);   
    //Serial.print("url_get = ");
    //Serial.println( temp_url);
  }


  if( connection_test == "null"){}
  else { 
    /*connection_test.toCharArray(temp_connection_test, serial.length()+1);
    strncpy(advance_json_serial, temp_connection_test, sizeof advance_json_serial);  */ 
    connection_test_F=1;
    send_to_server_F=1;
    //Serial.print("seial = ");
    //Serial.println( temp_serial);
  }


}

//{"error":"http_begin",}
//{"connection_test":"?",}
//{"serial":"100",}

//{"serial":"100","url":"SW_ENABLE=1&"}

