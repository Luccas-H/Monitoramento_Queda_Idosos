from flask import Flask, request, jsonify
from flask_cors import CORS
app = Flask(__name__)
CORS(app)

# Initialize a list to store patient data
patients = []

@app.route('/cadastrar', methods=['POST'])
def cadastrar():
    data = request.get_json()  # Receive the incoming data
    nome = data.get('nome')
    ala = data.get('ala')

    # Store the received data
    patients.append({'nome': nome, 'ala': ala})
    return jsonify({'message': 'Paciente cadastrado com sucesso!'}), 200

@app.route('/get_patients', methods=['GET'])
def get_patients():
    # Return all the patients in JSON format
    return jsonify(patients)

if __name__ == '__main__':
    app.run(debug=True)
