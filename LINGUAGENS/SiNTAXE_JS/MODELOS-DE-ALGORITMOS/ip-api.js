// Função assíncrona que aceita um IP como parâmetro opcional
async function getIPInfo(ip = '') {
    try {
        // Constrói a URL com ou sem IP específico
        const url = ip ? `http://ip-api.com/json/${ip}` : 'http://ip-api.com/json/';
        const response = await fetch(url);
        
        // Verifica se a requisição foi bem-sucedida
        if (!response.ok) {
            throw new Error('Erro na requisição: ' + response.status);
        }
        
        // Converte a resposta para JSON
        const data = await response.json();
        
        // Verifica se a API retornou sucesso
        if (data.status === 'success') {
            console.log('Informações de Geolocalização:');
            console.log('IP:', data.query);
            console.log('País:', data.country);
            console.log('Código do País:', data.countryCode);
            console.log('Região:', data.regionName);
            console.log('Código da Região:', data.region);
            console.log('Cidade:', data.city);
            console.log('CEP (se disponível):', data.zip || 'Não fornecido');
            console.log('Latitude:', data.lat);
            console.log('Longitude:', data.lon);
            console.log('Provedor de Internet:', data.isp);
            console.log('Organização:', data.org);
            console.log('AS:', data.as);
        } else {
            console.log('Falha na consulta:', data.message);
        }
    } catch (error) {
        console.error('Erro ao consultar a API:', error);
    }
}

// Exemplos de uso:
getIPInfo(); // Usa o IP público do usuário
getIPInfo('8.8.8.8'); // Consulta informações do IP 8.8.8.8 (Google DNS)