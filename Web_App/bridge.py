import paho.mqtt.client as mqtt
import serial
import time
import threading # 데이터 수신을 위한 스레드 추가 

# --- 시리얼 설정 ---
SERIAL_PORT = "/dev/ttyUSB0"  # 실제 포트 확인 필요
BAUD_RATE = 115200

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"✅ STM32 시리얼 연결 성공: {SERIAL_PORT}")
except Exception as e:
    print(f"❌ 시리얼 연결 실패: {e}")
    ser = None

# --- STM32로부터 데이터 읽기 함수 (추가) ---
def read_from_stm32():
    while ser and ser.is_open:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            if line:
                print(f"📡 STM32 응답: {line}") # 여기서 'A'가 찍혀야 함
# --- MQTT 콜백 ---
def on_connect(client, userdata, flags, rc, properties=None):
    if rc == 0:
        print("✅ MQTT 브로커 연결 성공!")
        client.subscribe("motor/control") # HTML과 동일한 토픽
    else:
        print(f"❌ 브로커 연결 실패: {rc}")

def on_message(client, userdata, msg):
    payload = msg.payload.decode().strip()
    print(f"📩 수신 데이터: {payload}")

    # STM32로 전송 (시리얼 연결이 살아있을 때만)
    if ser and ser.is_open:
        try:
            # 숫자로 변환 가능한지 체크 (데이터 정제)
            if payload.isdigit():
                # 전송 시 개행문자(\n)는 STM32 수신 인터럽트 종료 조건입니다.
                send_data = f"{payload}\n"
                ser.write(send_data.encode())
                print(f"➡️ STM32로 전송 완료: {send_data.strip()}") # 'A'가 포함되어 출력됨
        except Exception as e:
            print(f"❌ 시리얼 전송 중 에러: {e}")

# --- 실행 ---
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message

# 수신 전용 스레드 시작
rx_thread = threading.Thread(target=read_from_stm32, daemon=True)
rx_thread.start()

print("🚀 Bridge 프로그램 시작...")
client.connect("127.0.0.1", 1883, 60)
client.loop_forever()