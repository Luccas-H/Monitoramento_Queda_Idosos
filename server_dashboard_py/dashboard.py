import streamlit as st
import requests
import pandas as pd

# URL of your Flask server endpoint
FLASK_SERVER_URL = "http://127.0.0.1:5000/get_patients"

# Title and description
st.title("Dashboard de Pacientes")

# Function to fetch patients from Flask server
def fetch_patients():
    response = requests.get(FLASK_SERVER_URL)
    if response.status_code == 200:
        return response.json()
    else:
        st.error("Erro ao buscar dados dos pacientes.")
        return []

# Fetch and display the data
patients = fetch_patients()

# Display data in a table with style improvements
if patients:
    st.subheader("Lista de Pacientes Cadastrados")
    
    # Display the data as a styled table
    patient_df = pd.DataFrame(patients)
    st.write(patient_df.style.set_table_styles(
        [{'selector': 'thead th', 'props': [('background-color', '#4CAF50'), ('color', 'white')]},  # Header style
         {'selector': 'tbody tr:nth-child(odd)', 'props': [('background-color', '#f2f2f2')]},  # Alternating rows
         {'selector': 'tbody tr:nth-child(even)', 'props': [('background-color', '#ffffff')]},  # Alternating rows
         {'selector': 'td', 'props': [('padding', '10px')]},  # Cell padding
         {'selector': 'table', 'props': [('border-collapse', 'collapse'), ('width', '100%')]}]  # Table width
    ))

else:
    st.warning("Nenhum paciente cadastrado ainda. Cadastre um paciente para visualizar os dados.")
