# Phishing URL Detector - Documentation Summary

## Phase 4: Backend API Development

**Purpose:** Build FastAPI server that processes URLs through 5 analysis layers

**What it does:**
1. **Feature Extraction** - Analyzes URL patterns (length, characters, suspicious keywords)
2. **ML Prediction** - Loads trained model and predicts phishing probability (0-100%)
3. **Redirect Tracking** - Follows URL redirects to find final destination
4. **Content Fetching** - Safely retrieves page metadata without executing scripts
5. **Result Combination** - Packages everything into JSON response

**Key Files:**
```
backend/
├── app.py                     # Main API with /analyze endpoint
├── utils/
│   ├── feature_extractor.py   # Extracts 15+ features from URLs
│   ├── ml_predictor.py        # Loads model, predicts phishing score
│   ├── redirect_tracker.py    # Follows redirect chains
│   └── content_fetcher.py     # Fetches page title, status, metadata
└── models/
    └── phishing_detector.pkl  # Trained ML model
```

**API Response Example:**
```json
{
  "phishing_score": 87,
  "risk_level": "HIGH",
  "features": {...},
  "redirect_chain": [...],
  "page_info": {...}
}
```

---

## Phase 5: Streamlit Frontend Development

**Purpose:** Create user-friendly web interface for URL analysis

**What it does:**
1. **Input Section** - URL text box + example buttons
2. **Results Display** - Color-coded risk score (Green/Yellow/Red)
3. **Detailed Tabs** - ML Analysis, Redirect Chain, Page Info, Recommendations
4. **History Sidebar** - Shows recent analyses

**Key Features:**
- Real-time analysis with loading spinner
- Visual risk indicators (big percentage score)
- Feature breakdown highlighting suspicious elements
- Redirect visualization showing URL chain
- Action recommendations based on risk level

**Structure:**
```
frontend/
├── app.py              # Main Streamlit interface
└── utils/
    └── api_client.py   # Calls backend API
```

---

## Phase 6: Integration & Testing

**Purpose:** Connect frontend to backend and verify everything works

**What it does:**
1. **API Integration** - Frontend calls backend /analyze endpoint
2. **Error Handling** - Manages timeouts, connection errors, invalid URLs
3. **Test Suite** - Automated tests for phishing/legitimate/edge case URLs
4. **Performance Testing** - Ensures analysis completes in <3 seconds

**Test Categories:**
- Known phishing URLs (should score HIGH)
- Legitimate URLs (should score LOW)
- Edge cases (IP addresses, shortened URLs, long URLs)
- Error scenarios (empty URL, invalid format)

**Structure:**
```
tests/
└── test_suite.py      # Comprehensive automated tests
```

---

## Phase 7: Deployment

**Purpose:** Make the app publicly accessible

**Deployment Options:**

### 1. **Local Development**
```bash
# Terminal 1: Backend
uvicorn app:app --reload

# Terminal 2: Frontend
streamlit run app.py
```

### 2. **Streamlit Cloud (Frontend)**
- Push code to GitHub
- Connect repo at share.streamlit.io
- Instant public URL

### 3. **Render (Backend)**
```bash
# 1. Push to GitHub
git push origin main

# 2. Go to render.com → New Web Service
# 3. Connect your GitHub repo
# 4. Configure:
#    - Build Command: pip install -r requirements.txt
#    - Start Command: uvicorn app:app --host 0.0.0.0 --port $PORT
# 5. Deploy!
```
- Free tier available

**Structure:**
```
project/
├── backend/
│   ├── app.py
│   ├── utils/
│   ├── models/
│   └── requirements.txt
├── frontend/
│   ├── app.py
│   ├── utils/
│   └── requirements.txt
└── tests/
    └── test_suite.py
```

---

## Render Deployment (Backend)

### Configuration File

**File:** `backend/render.yaml`

```yaml
services:
  - type: web
    name: phishing-detector-api
    env: python
    buildCommand: pip install -r requirements.txt
    startCommand: uvicorn app:app --host 0.0.0.0 --port $PORT
    envVars:
      - key: PYTHON_VERSION
        value: 3.10.0
```

### Step-by-Step Deployment

1. **Prepare Backend**
```bash
cd backend
# Make sure requirements.txt exists
pip freeze > requirements.txt
```

2. **Push to GitHub**
```bash
git add .
git commit -m "Ready for Render deployment"
git push origin main
```

3. **Deploy on Render**
- Go to [render.com](https://render.com)
- Click "New +" → "Web Service"
- Connect your GitHub repository
- Select the `backend` directory (or root if backend is at root)
- Configure:
  - **Name:** phishing-detector-api
  - **Environment:** Python 3
  - **Build Command:** `pip install -r requirements.txt`
  - **Start Command:** `uvicorn app:app --host 0.0.0.0 --port $PORT`
- Click "Create Web Service"

4. **Get Your Backend URL**
- After deployment: `https://phishing-detector-api.onrender.com`
- Use this URL in your Streamlit frontend

5. **Update Frontend to Use Render Backend**

**File:** `frontend/app.py`
```python
# Change this line:
BACKEND_URL = "http://localhost:8000"

# To your Render URL:
BACKEND_URL = "https://phishing-detector-api.onrender.com"
```

### Render Free Tier Notes
- ✅ Free HTTPS included
- ✅ Auto-deploy on git push
- ⚠️ Spins down after 15 min of inactivity (first request may take 30s)
- ⚠️ 750 hours/month free

---

### Quick Start Guide

### Run Locally
```bash
# 1. Install dependencies
pip install -r requirements.txt

# 2. Start backend (Terminal 1)
cd backend
uvicorn app:app --reload --port 8000

# 3. Start frontend (Terminal 2)  
cd frontend
streamlit run app.py

# 4. Open browser: http://localhost:8501
```

### Deploy to Cloud
```bash
# 1. Push to GitHub
git push origin main

# 2. Deploy Backend to Render
# - Go to render.com
# - New Web Service → Connect GitHub repo
# - Build: pip install -r requirements.txt
# - Start: uvicorn app:app --host 0.0.0.0 --port $PORT

# 3. Deploy Frontend to Streamlit Cloud
# - Go to share.streamlit.io
# - Connect GitHub repo
# - Update BACKEND_URL to your Render URL
```

---

## File Overview

| Phase | File | Purpose |
|-------|------|---------|
| **4** | `backend/app.py` | Main API with /analyze endpoint |
| **4** | `utils/feature_extractor.py` | Extract URL features |
| **4** | `utils/ml_predictor.py` | ML model predictions |
| **4** | `utils/redirect_tracker.py` | Follow redirects |
| **4** | `utils/content_fetcher.py` | Fetch page metadata |
| **5** | `frontend/app.py` | Streamlit UI |
| **5** | `utils/api_client.py` | API communication |
| **6** | `tests/test_suite.py` | Automated tests |
| **7** | `render.yaml` | Render deployment config |
| **7** | `requirements.txt` | Python dependencies |

---

## Key Technologies

**Backend:**
- FastAPI (API framework)
- scikit-learn (ML model)
- requests (HTTP client)
- BeautifulSoup (HTML parsing)

**Frontend:**
- Streamlit (Web framework)
- pandas (Data display)
- plotly (Visualizations)

**Deployment:**
- Render (Backend hosting)
- Streamlit Cloud (Frontend hosting)
- GitHub (Version control)

---

## Time Estimates

- **Phase 4**: 3-4 hours (Backend development)
- **Phase 5**: 2-3 hours (Frontend development)
- **Phase 6**: 2-3 hours (Testing & integration)
- **Phase 7**: 1-2 hours (Deployment)

**Total**: 8-12 hours
