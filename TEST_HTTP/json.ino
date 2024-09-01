#define travel_time_addres "advance_settin*general*travel_time"
#define door_control_type_address "advance_settin*general*door*control_type"


void read_json(){

  char temp_json_name_w1[50];
  char temp_json_data_w1[50];

  char temp_json_name_r1[50];
  char temp_json_data_r1[50];

  //String data_json = doc["advance_settin*general*travel_time"];
  String json_name_w1 = doc["name_w1"];
  String json_data_w1 = doc["data_w1"];

  String json_name_r1 = doc["name_r1"];
  String json_data_r1 = doc["data_r1"];

  Serial.print("name_w1 = ");
  Serial.println( json_name_w1);
  Serial.print("data_w1 = ");
  Serial.println( json_data_w1);

  Serial.println( "  ------   " );

  Serial.print("name_r1 = ");
  Serial.println( json_name_r1);
  Serial.print("data_r1 = ");
  Serial.println( json_data_r1);

  //Serial.println( data_json.length() , DEC);

  Serial.println("-- JSON EXTEND ---");

  if( json_name_w1 == "null"){}
  else { 

    json_name_w1.toCharArray(temp_json_name_w1, json_name_w1.length()+1);
    Serial.print("name_w1 = ");
    Serial.println( temp_json_name_w1);
  }

  if( json_data_w1 == "null"){}
  else { 

    json_data_w1.toCharArray(temp_json_data_w1, json_data_w1.length()+1);
    Serial.print("data_w1 = ");
    Serial.println( temp_json_data_w1);
  }


  
  if( json_name_r1 == "null"){}
  else { 
    json_name_r1.toCharArray(temp_json_name_r1, json_name_r1.length()+1);
    Serial.print("name_r1 = ");
    Serial.println( temp_json_name_r1);
  }

  if( json_data_r1 == "null"){}
  else { 
    json_data_r1.toCharArray(temp_json_data_r1, json_data_r1.length()+1);
    Serial.print("data_r1 = ");
    Serial.println( temp_json_data_r1);
  }

  if( strcmp(temp_json_name_r1,travel_time_addres) == 0 ){ // reaf travel
    travel_time_send_F=1;
  }

  if( strcmp(temp_json_name_w1,travel_time_addres) == 0 ){ // write travel
    strncpy(travel_time, temp_json_data_w1, sizeof travel_time);   
  }


  if( strcmp(temp_json_name_r1,travel_time_addres) == 0 ){ // reaf travel
    travel_time_send_F=1;
  }

  if( strcmp(temp_json_name_r1,door_control_type_address) == 0 ){ // read door_control_type_address
    door_control_type_send_F=1;
  }


  if( strcmp(temp_json_name_w1,travel_time_addres) == 0 ){ // write travel
    strncpy(travel_time, temp_json_data_w1, sizeof travel_time);   
  }

  if( strcmp(temp_json_name_w1,door_control_type_address) == 0 ){ // write door_control_type_address
    strncpy(door_control_type, temp_json_data_w1, sizeof door_control_type);   
  }

  


  /*if( temp_json_name_w1 == ){

  }
    if( temp[0] == '@'){
      travel_time_send_F=1;
    }
    else{
      //strncpy(travel_time, data_json, sizeof travel_time);    
      data_json.toCharArray(travel_time, data_json.length()+1);
       Serial.println(travel_time);
    }

        */       

}