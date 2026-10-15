const mongoose = require('mongoose');

const readingSchema = new mongoose.Schema(
  {
    temperature: { type: Number, required: true },
    humidity: { type: Number, required: true },
    note: { type: String, default: '' },
  },
  { timestamps: true }
);

module.exports = mongoose.model('Reading', readingSchema);