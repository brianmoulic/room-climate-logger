require('dotenv').config();
const express = require('express');
const mongoose = require('mongoose');
const Reading = require('./models/Reading');

const app = express();
app.use(express.json());
app.use(express.static('public'));

mongoose
  .connect(process.env.MONGODB_URI)
  .then(() => console.log('Connected to MongoDB'))
  .catch((err) => console.error('MongoDB connection error:', err.message));

// CREATE: save a new reading
app.post('/api/readings', async (req, res) => {
  try {
    const reading = await Reading.create(req.body);
    res.status(201).json(reading);
  } catch (err) {
    res.status(400).json({ error: err.message });
  }
});

// READ: get all readings, newest first
app.get('/api/readings', async (req, res) => {
  try {
    const readings = await Reading.find().sort({ createdAt: -1 });
    res.json(readings);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

// READ: get only the newest reading
app.get('/api/readings/latest', async (req, res) => {
  try {
    const reading = await Reading.findOne().sort({ createdAt: -1 });
    if (!reading) return res.status(404).json({ error: 'No readings yet' });
    res.json(reading);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

// UPDATE: change the note of one reading
app.put('/api/readings/:id', async (req, res) => {
  try {
    const reading = await Reading.findByIdAndUpdate(
      req.params.id,
      { note: req.body.note },
      { new: true }
    );
    if (!reading) return res.status(404).json({ error: 'Reading not found' });
    res.json(reading);
  } catch (err) {
    res.status(400).json({ error: err.message });
  }
});

// DELETE: remove one reading
app.delete('/api/readings/:id', async (req, res) => {
  try {
    const reading = await Reading.findByIdAndDelete(req.params.id);
    if (!reading) return res.status(404).json({ error: 'Reading not found' });
    res.json({ message: 'Reading deleted' });
  } catch (err) {
    res.status(400).json({ error: err.message });
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));