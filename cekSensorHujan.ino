void cekSensorHujan()
{
  if (counterSample < 30)                     //sampling nilai now sampai 30x biar kelihatan perubahan nya
  {
    total = total - readings[readIndex];
    readings[readIndex] = analogRead(A5);
    total = total + readings[readIndex];
    readIndex = readIndex + 1;
    if (readIndex >= numReadings) {

      readIndex = 0;
    }
    now = total / numReadings;          //smoothing pembacaan tegangan analong per 10 cycle(biar stabil)

    //delay(1);                           //ngaruh?? bs dihapus
    if (awal == false && counterSample == 25) //Lonjakan voltage biar pembacaan gk salah (ambil nilai selisih awalan)
    {
      prev = now;
      awal = true;
    }
    // Serial.print("Now : ");
    //Serial.println(now);
    //    Serial.print("prev : ");
    //    Serial.println(prev);
    counterSample++;
  }
  else                              //nilai sampling 10x dikurangkan nilai pembacaan sebelum sampling
  {
    post = now - prev;

    if (abs(post) >= 10)             //cek perbedaan nilai jika lbh dari ....
    {
      Serial.println(abs(post));
      if (limitSW == LOW)
      {
        digitalWrite(7, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(2, LOW);
        mati = true;
      }
    }
    else if (abs(post) >= 0 && abs(post) <= 3 && mati == true)
    {
      digitalWrite(7, LOW);
      mati = false;
    }
    prev = now;
    counterSample = 0;
  }
}
